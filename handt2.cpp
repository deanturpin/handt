#include "pairs.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

template <typename T>
auto buy_strategy(const T historic, const T current, const T future,
                  const double buy, const double sell) {
  if (*current / *historic > buy) {

    // Find the first opportunity to sell in the future sell window
    return std::find_if(current, future, [&current, &sell](const auto &p) {
      return p > (*current * sell);
    });
  }

  else
    return historic;
}

int main() {

  // A currency pair is a duo of symbols and an exchange whence the price came
  // struct currency_pair {
  //   std::string from_sym{};
  //   std::string to_sym{};
  //   std::string exchange{};
  // };

  // Get prices
  for (const auto &file : std::filesystem::directory_iterator("tmp")) {

    // Open each coin summary
    std::ifstream in(file.path());

    // Get the trade details
    std::string from_sym, to_sym, exchange;
    in >> from_sym >> to_sym >> exchange;

    std::cout << from_sym << '-' << to_sym << '\t' << exchange << '\n';

    // Get the prices
    const std::vector<double> prices{std::istream_iterator<double>(in), {}};

    if (!prices.empty()) {

      // Backtest
      std::cout << std::accumulate(prices.cbegin(), prices.cend(), 0.0) /
                       prices.size()
                << " average price\n";

      // Configure trading period
      const unsigned int analysis_window = 24;
      const unsigned int sell_window = analysis_window * 2;

      // Set up some indices into the prices. Historic price the first price in
      // the analysis window and the future price is the furthest price after
      // the current price that we're prepared to trade.

      // |-- analysis window --|
      // H--------------------NOW-----------------F
      //                       |-- trade window --|

      // Initialise the price markers to the beginning of the historic price
      // data
      auto historic_price = prices.cbegin();
      auto current_price = std::next(historic_price, analysis_window);
      auto future_price = std::next(current_price, sell_window);

      // Stat reporting
      unsigned int successes = 0;
      unsigned int fails = 0;
      unsigned int opportunities_to_trade = 0;

      while (future_price < prices.cend()) {

        // Define our trading thresholds
        const double buy_threshold = 1.15;
        const double sell_threshold = 1.05;

        // The buy strategy: return true if the strategy has triggered for the
        // given range of historic prices
        const auto buy_strategy = [](const auto &historic, const auto &current,
                                     const double &threshold) -> bool {
          // return *current / *historic > threshold;
          return *historic / *current > threshold;
        };

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
            ++successes;

            // If we succeeded move the next analysis window so it starts at
            // the sell price
            historic_price = sell_price;
          } else
            ++fails;
        }

        // Nudge the analysis window along
        std::advance(historic_price, 1);

        // Update upstream prices
        current_price = std::next(historic_price, analysis_window);
        future_price = std::next(current_price, sell_window);

        // Track how many times we could have traded
        ++opportunities_to_trade;
      }

      std::cout << successes << " successes, " << fails << " fails, "
                << opportunities_to_trade << " opportunities to trade\n";

      std::cout << (fails > 0.0 ? 100.0 * successes / (successes + fails) : 0.0)
                << " % success rate\n";
    } else
      std::cout << "BAD COIN\n";
  }
}
