#include "pairs.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

int main() {

  struct strategy_summary {
    std::string from_symbol{"undefined"};
    std::string to_symbol{"undefined"};
    std::string exchange{"undefined"};
    unsigned int opportunities_to_trade{0u};
    unsigned int good_deals{0u};
    unsigned int bad_deals{0u};
    double average_price{0u};

    void print() const {
      std::cout << from_symbol << '-' << to_symbol << ' ' << exchange << ' '
                << average_price << ' ' << good_deals << " good " << bad_deals
                << " bad " << opportunities_to_trade << " opportunities\n";
    }
  };

  // Create a
  static std::vector<strategy_summary> summary;
  summary.reserve(pairs.size());

  // Get prices
  for (const auto &file : std::filesystem::directory_iterator("tmp")) {

    using iter = const std::vector<double>::const_iterator &;
    using func = const std::function<bool(iter, iter, const double &)>;
    using thresh = const double &;

    // The buy strategies: return true if the strategy has triggered for the
    // given range of historic prices
    func strategy1 = [](iter historic, iter current, thresh threshold) {
      return *historic / *current > threshold;
    };

    func strategy2 = [](iter historic, iter current, thresh threshold) {
      return *current / *historic > threshold;
    };

    func strategy3 = [](iter historic, iter current, thresh threshold) {
      return *std::max_element(historic, std::prev(current)) /
                 *std::prev(current) >
             threshold;
    };

    func strategy4 = [](iter historic, iter current, thresh threshold) {
      return *std::prev(current) /
                 *std::max_element(historic, std::prev(current)) >
             threshold;
    };

    func strategy5 = [](iter historic, iter current, thresh threshold) {
      return *std::prev(current) / (std::accumulate(historic, current, 0.0) /
                                    std::distance(historic, current)) >
             threshold;
    };

    for (const auto &buy_strategy :
         {strategy1, strategy2, strategy3, strategy4, strategy5}) {

      // Open each coin summary
      std::ifstream in(file.path());

      // Create a new strategy summary to populate
      strategy_summary &strategy = summary.emplace_back(strategy_summary{});

      // Get the trade details
      in >> strategy.from_symbol >> strategy.to_symbol >> strategy.exchange;

      // Get the prices
      const std::vector<double> prices{std::istream_iterator<double>(in), {}};

      if (!prices.empty()) {

        // Backtest
        strategy.average_price =
            std::accumulate(prices.cbegin(), prices.cend(), 0.0) /
            prices.size();

        // Configure trading period
        const unsigned int analysis_window = 24;
        const unsigned int sell_window = analysis_window * 2;

        // Set up some indices into the prices. Historic price the first price
        // in the analysis window and the future price is the furthest price
        // after the current price that we're prepared to trade.

        // |-- analysis window --|
        // H--------------------NOW-----------------F
        //                       |-- trade window --|

        // Initialise the price markers to the beginning of the historic price
        // data
        auto historic_price = prices.cbegin();
        auto current_price = std::next(historic_price, analysis_window);
        auto future_price = std::next(current_price, sell_window);

        while (future_price < prices.cend()) {

          // Define our trading thresholds
          const double buy_threshold = 1.30;
          const double sell_threshold = 1.1;

          // The sell strategy: return the index of the first price to exceed
          // the sell threshold or return the end iterator
          const auto sell_strategy = [](const auto &current, const auto &future,
                                        const double &threshold) {
            const double spot = *current;
            return std::find_if(current, future,
                                [&spot, &threshold](const auto &p) {
                                  return p > spot * threshold;
                                });
          };

          if (buy_strategy(historic_price, current_price, buy_threshold)) {

            // Strategy triggered, so look ahead to see if it succeeded in the
            // defined trade window
            if (const auto sell_price =
                    sell_strategy(current_price, future_price, sell_threshold);
                sell_price != future_price) {
              ++strategy.good_deals;

              // If we succeeded move the next analysis window so it starts at
              // the sell price
              historic_price = sell_price;
            } else
              ++strategy.bad_deals;
          }

          // Nudge the analysis window along
          std::advance(historic_price, 1);

          // Update upstream prices
          current_price = std::next(historic_price, analysis_window);
          future_price = std::next(current_price, sell_window);

          // Track how many times we could have traded
          ++strategy.opportunities_to_trade;
        }
      }
    }
  }

  for (const auto &s : summary)
    s.print();
}
