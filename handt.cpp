#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <vector>

namespace handt {

// Define the buy strategies: each strategy function takes a subset of
// available prices - the analysis window - and returns a threshold to
// determine whether to buy or not
using cont = const std::vector<double> &;
using func = std::function<double(cont)>;

// A complete strategy consists of a primary and secondary strategy and a buy
// threshold

struct strategy_combo {
  std::string name;
  std::function<bool(cont)> primary;
  std::function<double(cont)> secondary;
  int threshold;
};

// Primary strategies are simple boolean tests
const std::map<std::string, std::function<bool(cont)>> primary_strategies{

    // Always return positively
    {"crouching",
     [](cont p) {
       static_cast<void>(p);
       return true;
     }},

    // Return positively if trending upwards
    {"leaping",
     [](cont p) {
       unsigned int trend = 0;
       for (auto i = p.cbegin(); i != std::prev(p.cend()); ++i)
         if (*i < *std::next(i))
           ++trend;

       return trend > p.size() / 2;
     }},

    // Return positively if trending downwards
    {"supine",
     [](cont p) {
       unsigned int trend = 0;
       for (auto i = p.cbegin(); i != std::prev(p.cend()); ++i)
         if (*i > *std::next(i))
           ++trend;

       return trend > p.size() / 2;
     }},

    // Return positively if crossing a significant boundary
    {"straddling",
     [](cont p) {
       const auto &[min, max] = std::minmax(p.front(), p.back());

       unsigned long threshold = 0;
       for (const unsigned long &mod : {1, 10, 100, 1000, 10000}) {

         const unsigned long test =
             max - (static_cast<unsigned long>(max) % mod);

         if (test == 0)
           break;

         threshold = test;
       }

       return min < threshold && max > threshold;
     }},
};

// Secondary strategies yield a threshold which is interpreted as a buy
// threshold
const std::map<std::string, func> secondary_strategies{

    {"cipher", [](cont p) { return p.front() / p.back(); }},
    {"forest", [](cont p) { return p.back() / p.front(); }},

    {"xoloitzcuintli",
     [](cont p) {
       return (std::accumulate(p.cbegin(), p.cend(), 0.0) / p.size()) /
              p.back();
     }},

    {"affenpinscher",
     [](cont p) {
       return p.back() /
              (std::accumulate(p.cbegin(), p.cend(), 0.0) / p.size());
     }},

    {"basenji",
     [](cont p) {
       return (std::accumulate(p.cbegin(), p.cend(), 0.0) / p.size()) /
              p.front();
     }},

    {"owl",
     [](cont p) {
       return p.front() /
              (std::accumulate(p.cbegin(), p.cend(), 0.0) / p.size());
     }},

    {"capybara",
     [](cont p) {
       const auto filt = p.size() / 2;
       return std::accumulate(p.cbegin(), std::prev(p.cend(), filt), 0.0) /
              std::accumulate(std::next(p.cbegin(), filt), p.cend(), 0.0);
     }},

    {"tarantula",
     [](cont p) {
       const auto filt = p.size() / 2;
       return std::accumulate(std::next(p.cbegin(), filt), p.cend(), 0.0) /
              std::accumulate(p.cbegin(), std::prev(p.cend(), filt), 0.0);
     }},

    {"bandicoot",
     [](cont p) {
       const auto filt = p.size() / 2;
       return std::accumulate(std::next(p.cbegin(), filt), p.cend(), 0.0) /
              std::accumulate(p.cbegin(), p.cend(), 0.0);
     }},

    {"badger",
     [](cont p) {
       const auto filt = p.size() / 2;
       return std::accumulate(p.cbegin(), p.cend(), 0.0) /
              std::accumulate(std::next(p.cbegin(), filt), p.cend(), 0.0);
     }},

    {"caddisfly",
     [](cont p) {
       const auto val =
           p.back() / *std::max_element(p.cbegin(), std::prev(p.cend()));
       return std::isinf(val) ? 0.0 : val;
     }},

    {"griffon",
     [](cont p) {
       return *std::max_element(p.cbegin(), std::prev(p.cend())) / p.back();
     }},

    {"narwahl",
     [](cont p) {
       return p.front() / *std::max_element(std::next(p.cbegin()), p.cend());
     }},

    {"cricket",
     [](cont p) {
       return *std::max_element(std::next(p.cbegin()), p.cend()) / p.front();
     }},

    {"axolotl",
     [](cont p) {
       return p.back() / *std::min_element(p.cbegin(), std::prev(p.cend()));
     }},

    {"mink",
     [](cont p) {
       return *std::min_element(p.cbegin(), std::prev(p.cend())) / p.back();
     }},

    {"tiger",
     [](cont p) {
       const auto min = *std::min_element(std::next(p.cbegin()), p.cend());
       return min > 0.0 ? p.front() / min : 0.0;
     }},

    {"ocelot",
     [](cont p) {
       return *std::min_element(std::next(p.cbegin()), p.cend()) / p.front();
     }},
};

// The sell strategy: return the index of the first price to exceed
// the sell threshold or return the end iterator
using iter = const std::vector<double>::const_iterator &;
auto sell(iter current, iter future) {
  return std::find_if(current, future,
                      [spot = *current](const auto &future_price) {
                        return future_price > spot * 1.05;
                      });
}
} // namespace handt

int main() {

  // Create a set of thresholds to use with each buy strategy
  std::vector<int> thresholds(20);
  std::iota(thresholds.begin(), thresholds.end(), 2);

  // Create and initialise a container of all strategy permuations
  static std::vector<handt::strategy_combo> permutations;
  const auto total_permutations = handt::primary_strategies.size() *
                                  handt::secondary_strategies.size() *
                                  thresholds.size();
  permutations.reserve(total_permutations);

  // Populate with the strategy library
  for (const auto &[name1, buy1] : handt::primary_strategies)
    for (const auto &[name2, buy2] : handt::secondary_strategies)
      for (const auto &threshold : thresholds)
        permutations.push_back(
            {name1 + ' ' + name2 + ' ' + std::to_string(threshold), buy1, buy2,
             threshold});

  std::vector<std::string> currency_pairs;
  for (const auto &file : std::filesystem::directory_iterator("tmp"))
    currency_pairs.emplace_back(file.path());

  struct strategy_performance {
    std::string name;
    std::string from_symbol;
    std::string to_symbol;
    std::string exchange;
    unsigned int good_deals = 0;
    unsigned int bad_deals = 0;
  };

  // We will report a summary of all strategies against all currency pairs
  std::list<strategy_performance> performance;

  // Extract prices from each file
  for (const auto &file : currency_pairs) {

    // Open prices and get the trade info
    std::ifstream in(file);
    std::string from_symbol, to_symbol, exchange;
    in >> from_symbol >> to_symbol >> exchange;

    // Get the prices and run the strategies over them
    const std::vector<double> prices{std::istream_iterator<double>(in), {}};

    if (!prices.empty())
      for (const auto &strat : permutations) {

        // Create a new strategy and add it to the summary for later
        auto &perf = performance.emplace_back(
            strategy_performance{strat.name, from_symbol, to_symbol, exchange});

        // Configure trading periods for back test
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

          // Calculate the buy ratio
          const double ratio = (100.0 + strat.threshold) / 100;

          // Test strategy
          if (strat.primary({historic_price_index, current_price_index}) &&
              strat.secondary({historic_price_index, current_price_index}) >
                  ratio) {

            // Strategy triggered, so look ahead to see if it succeeded in
            // the defined trade window
            if (const auto sell_price_index =
                    handt::sell(current_price_index, future_price_index);
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
        }
      }
  }

  // Sort strategies by performance
  performance.sort([](const auto &a, const auto &b) {
    return (a.good_deals ? a.good_deals : 1.0) /
               (a.bad_deals ? a.bad_deals : 1.0) >
           (b.good_deals ? b.good_deals : 1.0) /
               (b.bad_deals ? b.bad_deals : 1.0);
  });

  // Pretty print numbers
  std::cout.imbue(std::locale(""));

  // Strategy and trade overview
  std::cout << currency_pairs.size() << " currency pairs, "
            << handt::primary_strategies.size() << " primary strategies, "
            << handt::secondary_strategies.size() << " secondary strategies, "
            << thresholds.size() << " thresholds, (" << permutations.size()
            << " strategy permutations), " << performance.size()
            << " tests performed.\n\n";

  // Print strategy reports
  std::cout << "Strategy|Pair|Good/Bad\n";
  std::cout << "---|---|---\n";

  for (const auto &s : performance)
    std::cout << s.name << '|' << s.from_symbol << '-' << s.to_symbol << '|'
              << s.good_deals << '/' << s.bad_deals << '\n';
}
