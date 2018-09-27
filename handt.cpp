#include "handt.h"
#include "prices.h"
#include "report.h"
#include <list>
#include <vector>

const auto have_a_nice_day_trader = [](const auto &pr) {
  // Create a set of thresholds to use with each buy strategy
  std::vector<int> thresholds(22);
  std::iota(thresholds.begin(), thresholds.end(), 2);

  // A complete strategy consists of a primary and secondary strategy and a buy
  // threshold
  struct strategy_combo {
    std::string name;
    handt::func1 primary;
    handt::func2 secondary;
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

      // Check we haven't ended up with a huge number/nan by inadvertantly
      // dividing a double with a very similar double or zero, and then return
      // strategy success
      return !std::isinf(secondary_response) && !std::isnan(primary_response) &&
             primary_response && secondary_response > ratio;
    }
  };

  // Create and all strategy permutations up front
  const auto total_permutations = handt::primary_strategies.size() *
                                  handt::secondary_strategies.size() *
                                  thresholds.size();
  std::vector<strategy_combo> permutations;
  permutations.reserve(total_permutations);

  // Populate with strategies from the handt library
  for (const auto &[name1, buy1] : handt::primary_strategies)
    for (const auto &[name2, buy2] : handt::secondary_strategies)
      for (const auto &threshold : thresholds)
        permutations.push_back(
            {name1 + ' ' + name2 + ' ' + std::to_string(threshold), buy1, buy2,
             threshold});

  std::list<strategy_performance> performance;

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

  for (const auto &[from_symbol, to_symbol, exchange, prices] : pr) {

    // Check read has succeeded and execute strategies
    if (!prices.empty())
      for (const auto &strat : permutations) {

        // Create a new strategy and add it to the summary for later
        const auto spot = prices.back();
        auto &perf = performance.emplace_back(strategy_performance{
            strat.name, from_symbol, to_symbol, exchange, spot});

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
        auto historic_price_index = prices.cbegin();
        auto current_price_index =
            std::next(historic_price_index, analysis_window);
        auto future_price_index = std::next(current_price_index, sell_window);

        // Move windows along until we run out of prices
        while (future_price_index < prices.cend()) {

          // Test strategy
          if (strat.execute(historic_price_index, current_price_index)) {

            // Strategy triggered, so look ahead to see if it succeeded in
            // the defined trade window
            if (const auto sell_price_index =
                    sell(current_price_index, future_price_index);
                sell_price_index != future_price_index) {
              ++perf.good_deals;

              // Move the analysis window so the next iteration starts at
              // the last sell price
              historic_price_index = sell_price_index;
            } else
              ++perf.bad_deals;
          }

          // Nudge the analysis window along and update upstream prices
          std::advance(historic_price_index, 1);
          current_price_index =
              std::next(historic_price_index, analysis_window);
          future_price_index = std::next(current_price_index, sell_window);

          // Record that this was an opportunity to trade
          ++perf.opportunities;
        }

        // Calculate prospects using the most recent prices
        historic_price_index = std::prev(prices.cend(), analysis_window);
        current_price_index = prices.cend();

        if (strat.execute(historic_price_index, current_price_index))
          perf.buy = true;
      }
  }

  // Sort strategies by performance - we don't want to divide by zero be also
  // want zero denominators or numerators to sort nicely
  performance.sort([](const auto &a, const auto &b) {
    return static_cast<double>(a.good_deals ? a.good_deals : .9) /
               (a.bad_deals ? a.bad_deals : .9) >
           static_cast<double>(b.good_deals ? b.good_deals : .9) /
               (b.bad_deals ? b.bad_deals : .9);
  });

  return performance;
};

int main() {

  // Unit test
  handt::unit_test();

  // Fetch the latest prices and have a nice day (trader)
  report_performance(have_a_nice_day_trader(get_prices()));
}
