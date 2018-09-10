#include "pairs.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <functional>
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

    std::string str() const {
      std::stringstream out;
      out << from_symbol << '-' << to_symbol << ' ' << exchange << ' '
          << average_price << ' ' << good_deals << " good " << bad_deals
          << " bad " << opportunities_to_trade << " opportunities";

      return out.str();
    }
  };

  // Create a
  static std::vector<strategy_summary> summary;
  summary.reserve(pairs.size());

  // Get prices
  for (const auto &file : std::filesystem::directory_iterator("tmp")) {

    // The buy strategies: return true if the strategy has triggered for the
    // given range of historic prices
    using iter = const std::vector<double>::const_iterator &;
    using func = std::function<double(iter, iter)>;
    const std::vector<func> strategies{
        [](iter historic, iter current) { return *historic / *current; },
        [](iter historic, iter current) { return *current / *historic; },
        [](iter historic, iter current) {
          return *std::max_element(historic, std::prev(current)) /
                 *std::prev(current);
        },
        [](iter historic, iter current) {
          return *std::prev(current) /
                 *std::max_element(historic, std::prev(current));
        },
        [](iter historic, iter current) {
          return *std::prev(current) /
                 (std::accumulate(historic, current, 0.0) /
                  std::distance(historic, current));
        },
        [](iter historic, iter current) {
          return (std::accumulate(historic, current, 0.0) /
                  std::distance(historic, current)) /
                 *std::prev(current);
        },
    };

    // Open prices
    std::ifstream in(file.path());
    std::string from_symbol, to_symbol, exchange;

    // Get the trade details
    in >> from_symbol >> to_symbol >> exchange;

    // Get the prices
    if (const std::vector<double> prices{std::istream_iterator<double>(in), {}};
        !prices.empty()) {

      // Run strategies over the prices
      for (const auto &buy_strategy : strategies) {

        // Create a new strategy summary, initialised with basic trade info
        strategy_summary &strategy = summary.emplace_back(
            strategy_summary{from_symbol, to_symbol, exchange});

        strategy.average_price =
            std::accumulate(prices.cbegin(), prices.cend(), 0.0) /
            prices.size();

        // Configure trading periods for back test
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

        // Move windows along until we run out of prices
        while (future_price < prices.cend()) {

          // The sell strategy: return the index of the first price to exceed
          // the sell threshold or return the end iterator
          const auto sell_strategy = [](iter current, iter future) {
            return std::find_if(current, future, [&current](const auto &p) {
              return p > *current * 1.05;
            });
          };

          // Test strategy
          const double buy_threshold = 1.15;
          if (buy_strategy(historic_price, current_price) > buy_threshold) {

            // Strategy triggered, so look ahead to see if it succeeded in the
            // defined trade window
            if (const auto sell_price =
                    sell_strategy(current_price, future_price);
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

  // Sort strategies by effectiveness
  std::sort(summary.begin(), summary.end(), [](const auto &a, const auto &b) {
    const auto a_performance = a.bad_deals > 0.0
                                   ? a.good_deals / (a.good_deals + a.bad_deals)
                                   : a.good_deals;
    const auto b_performance = b.bad_deals > 0.0
                                   ? b.good_deals / (b.good_deals + b.bad_deals)
                                   : b.good_deals;

    return a_performance < b_performance;
  });

  // Print strategy report
  for (const auto &s : summary)
    std::puts(s.str().c_str());
}
