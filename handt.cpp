#include "handt.h"
#include "prices.h"
#include "strategy.h"
#include <algorithm>
#include <cmath>
#include <list>
#include <numeric>
#include <vector>

// Take a container of prices and run all strategies permutations

std::list<backtest_t> have_a_nice_day_trader(const prices_t &prices) {

  // Create a set of thresholds to use with each buy strategy
  std::vector<int> thresholds(22);
  std::iota(thresholds.begin(), thresholds.end(), 2);

  // A complete strategy consists of a primary and secondary strategy and a buy
  // threshold
  struct strategy_t {
    std::string name;
    lft::func1 primary;
    lft::func2 secondary;
    int threshold;
    using iter = const std::vector<double>::const_iterator &;
    bool execute(iter historic_price_index, iter current_price_index) const {

      // Calculate the buy ratio
      const double ratio = (100.0 + threshold) / 100.0;

      // Test the strategies
      const auto primary_response =
          primary({historic_price_index, current_price_index});
      const auto secondary_response =
          secondary({historic_price_index, current_price_index});

      // Check we haven't ended up with a huge number (or NaN) by inadvertantly
      // dividing a double with a very similar double (or zero), and then
      // return strategy success
      return !std::isinf(secondary_response) && !std::isnan(primary_response) &&
             primary_response && secondary_response > ratio;
    }
  };

  // Create and all strategy permutations up front
  const auto total_permutations = lft::primary_strategies.size() *
                                  lft::secondary_strategies.size() *
                                  thresholds.size();
  std::vector<strategy_t> permutations;
  permutations.reserve(total_permutations);

  // Populate with strategies from the handt library
  for (const auto &[name1, buy1] : lft::primary_strategies)
    for (const auto &[name2, buy2] : lft::secondary_strategies)
      for (const auto &threshold : thresholds)
        permutations.push_back(
            {name1 + ' ' + name2 + ' ' + std::to_string(threshold), buy1, buy2,
             threshold});

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
  std::list<backtest_t> backtests;
  for (const auto &[from_symbol, to_symbol, exchange, latest] : prices) {

    // Execute all strategy permutuation
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
            ++backtest.good_deals;

            // Move the analysis window so the next iteration starts at
            // the last sell price
            historic_price_index = sell_price_index;
          } else
            ++backtest.bad_deals;
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

  // Sort strategies by performance - we don't want to divide by zero be also
  // want zero denominators or numerators to sort nicely
  backtests.sort([](const auto &a, const auto &b) {
    return static_cast<double>(a.good_deals ? a.good_deals : .9) /
               (a.bad_deals ? a.bad_deals : .9) >
           static_cast<double>(b.good_deals ? b.good_deals : .9) /
               (b.bad_deals ? b.bad_deals : .9);
  });

  return backtests;
}
