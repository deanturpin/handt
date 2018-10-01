#include "backtest.h"
#include "perms.h"
#include "prices.h"
#include <algorithm>
#include <numeric>
#include <vector>

// Take a container of prices and run all strategies permutations

std::vector<backtest_t>
run_backtests(const prices_t &prices,
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
  for (const auto &[from_symbol, to_symbol, exchange, latest] : prices) {

    // Execute all strategy permutation
    for (const auto &strat : permutations) {

      // Create a new strategy and add it to the summary for later
      const auto spot = latest.back();
      auto &backtest = backtests.emplace_back(
          backtest_t{strat.name, from_symbol, to_symbol, exchange, spot});

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

      // Initialise the price markers to the start of historic price data
      auto historic_price_index = latest.cbegin();
      auto current_price_index =
          std::next(historic_price_index, analysis_window);
      auto future_price_index = std::next(current_price_index, sell_window);

      // Move windows along until we run out of prices
      while (future_price_index < latest.cend()) {

        // Test strategy
        if (strat.execute(historic_price_index, current_price_index)) {

          // Strategy triggered, so look ahead to see if it succeeded in
          // the defined trade window
          if (const auto sell_price_index =
                  sell(current_price_index, future_price_index);
              sell_price_index != future_price_index) {

            const int buy_index =
                std::distance(latest.cbegin(), current_price_index);
            const int sell_index =
                std::distance(latest.cbegin(), sell_price_index);

            backtest.good_deals.push_back({buy_index, sell_index});

            // Move the analysis window so the next iteration starts at
            // the last sell price
            historic_price_index = sell_price_index;
          } else
            backtest.bad_deals.push_back({0, 0});
        }

        // Nudge the analysis window along and update upstream prices
        std::advance(historic_price_index, 1);
        current_price_index = std::next(historic_price_index, analysis_window);
        future_price_index = std::next(current_price_index, sell_window);

        // Record that this was an opportunity to trade
        ++backtest.opportunities;
      }

      // Calculate prospects using the most recent prices
      historic_price_index = std::prev(latest.cend(), analysis_window);
      current_price_index = latest.cend();

      if (strat.execute(historic_price_index, current_price_index))
        backtest.buy = true;
    }
  }

  stable_sort(
      backtests.begin(), backtests.end(), [](const auto &a, const auto &b) {
        return static_cast<double>(a.good_deals.size() ? a.good_deals.size()
                                                       : .9) /
                   (a.bad_deals.size() ? a.bad_deals.size() : .9) >
               static_cast<double>(b.good_deals.size() ? b.good_deals.size()
                                                       : .9) /
                   (b.bad_deals.size() ? b.bad_deals.size() : .9);
      });

  return backtests;
}
