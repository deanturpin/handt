#include "backtest.h"
#include "parallel.h"
#include "perms.h"
#include "trade.h"
#include <algorithm>
#include <numeric>
#include <vector>

// Take a container of prices and run all strategy permutations over them

std::vector<backtest_t>
run_backtests(const std::vector<trade_t> &trades,
              const std::vector<strategy_t> &permutations) {

  // The sell strategy returns positively if the expected yield is acheived
  // within the trading window
  const double sell_threshold = 6;
  const auto sell = [&sell_threshold](const auto &current, const auto &future) {
    return std::find_if(
        current, future,
        [spot = *current, threshold = (100.0 + sell_threshold) /
                                      100.0](const auto &future_price) {
          return future_price > spot * threshold;
        });
  };

  // Backtest each currency pair
  std::vector<backtest_t> backtests;
  for (const auto &[from_symbol, to_symbol, exchange, prices] : trades) {

    // Construct all strategy permutations
    for (const auto &strategy : permutations) {

      // Create a new strategy and add it to the summary for later
      const auto spot = prices.back();
      backtests.emplace_back(backtest_t{strategy.name, from_symbol, to_symbol,
                                        exchange, spot, strategy});
    }
  }

  // Execute trades
  parallel::for_each(
      backtests.begin(), backtests.end(), [&sell, &trades](auto &backtest) {
        // Configure trading periods for backtest
        const unsigned int analysis_window = 24;
        const unsigned int sell_window = analysis_window * 2;

        // Set up some indices into the prices. Historic price is the first
        // price in the analysis window and the future price is the furthest
        // price after the current price that we're prepared to trade. e.g.,
        // 24-hour analysis window and 48-hour trade window

        // |-- analysis window --|
        // H--------------------NOW-----------------F
        //                       |-- trade window --|

        // Find some prices for our trade
        const auto it = find_if(
            trades.cbegin(), trades.cend(),
            [from_symbol = backtest.from_symbol, to_symbol = backtest.to_symbol,
             exchange = backtest.exchange](const auto &t) {
              return t.from_symbol == from_symbol && t.to_symbol == to_symbol &&
                     t.exchange == exchange;
            });

        // If we've found some prices set up reference
        if (it != trades.cend()) {

          const auto &prices = it->prices;

          // Initialise the price markers to the start of historic price data
          auto historic_price_index = prices.cbegin();
          auto current_price_index =
              std::next(historic_price_index, analysis_window);
          auto future_price_index = std::next(current_price_index, sell_window);

          // Move windows along until we run out of prices
          while (future_price_index < prices.cend()) {

            // Test strategy
            if (backtest.strategy.execute(historic_price_index,
                                          current_price_index)) {

              // Strategy triggered, so look ahead to see if it succeeded in
              // the defined trade window
              if (const auto sell_price_index =
                      sell(current_price_index, future_price_index);
                  sell_price_index != future_price_index) {

                const int buy_index =
                    std::distance(prices.cbegin(), current_price_index);
                const int sell_index =
                    std::distance(prices.cbegin(), sell_price_index);

                backtest.good_deals.push_back({buy_index, sell_index});

                // Move the analysis window so the next iteration starts at
                // the last sell price
                historic_price_index = sell_price_index;
              } else
                backtest.bad_deals.push_back({0, 0});
            }

            // Nudge the analysis window along and update upstream prices
            std::advance(historic_price_index, 1);
            current_price_index =
                std::next(historic_price_index, analysis_window);
            future_price_index = std::next(current_price_index, sell_window);

            // Record that this was an opportunity to trade
            ++backtest.opportunities;
          }

          // Calculate prospects using the most recent prices
          historic_price_index = std::prev(prices.cend(), analysis_window);
          current_price_index = prices.cend();

          if (backtest.strategy.execute(historic_price_index,
                                        current_price_index))
            backtest.buy = true;
        }
      });

  // Sort backtests by success
  std::stable_sort(
      backtests.begin(), backtests.end(), [](const auto &a, const auto &b) {
        const unsigned int agd = a.good_deals.size();
        const unsigned int bgd = b.good_deals.size();
        const unsigned int abd = a.bad_deals.size();
        const unsigned int bbd = b.bad_deals.size();

        return static_cast<double>(agd ? agd : .9) / (abd ? abd : .9) >
               static_cast<double>(bgd ? bgd : .9) / (bbd ? bbd : .9);
      });

  return backtests;
}
