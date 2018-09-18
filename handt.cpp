#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <vector>

namespace handt {

// Define the buy strategies: each strategy function takes a subset of
// available prices - the analysis window - and returns a threshold to
// determine whether to buy or not
using cont = const std::vector<double> &;
using func = std::function<double(cont)>;
using func1 = std::function<bool(cont)>;
using func2 = std::function<double(cont)>;

// A complete strategy consists of a primary and secondary strategy and a buy
// threshold

struct strategy_combo {
  std::string name;
  func1 primary;
  func2 secondary;
  int threshold;
};

// Structure to represent a trade
// struct strategy_summary {
//   std::string from_symbol = "undefined";
//   std::string to_symbol = "undefined";
//   std::string exchange = "undefined";
//   func primary;
//   func secondary;
//   double threshold = 0.0;
//   unsigned int opportunities_to_trade = 0u;
//   unsigned int good_deals = 0u;
//   unsigned int bad_deals = 0u;
//   double spot = 0u;
//   bool current_prospect = false;
//   double trigger_ratio = 0.0;
//
//   // Construct strategy summary
//   std::string str() const {
//     const std::string currency_pair = from_symbol + '-' + to_symbol;
//
//     std::stringstream out;
//     // out << primary << ' ' << secondary << ' ' << -100.0 + threshold *
//     100.0
//     //     << " %|[" << currency_pair << "](" << url() << ")|" << good_deals
//     //     << '/' << bad_deals << '|' << spot << '|' <<
//     opportunities_to_trade
//     //     << '|' << std::fixed << std::setprecision(0)
//     //     << -100.0 + 100.0 * trigger_ratio << " %|"
//     //     << (current_prospect ? " *" : "");
//     return out.str();
//   }
//
//   // Construct strategy table heading
//   std::string heading() const {
//     std::stringstream out;
//     out << "Strategy|Pair|Good/Bad|Spot|Tests|Threshold|BUY NOW!\n";
//     out << "---|---|---|---|---|---|---";
//     return out.str();
//   }
//
//   // Construct exchange URL
//   std::string url() const {
//     return exchange == std::string("Coinbase")
//                ? "http://coinbase.com"
//                : exchange == std::string("Binance")
//                      ? "https://www.binance.com/en/trade/" + from_symbol +
//                      '_' +
//                            to_symbol
//                      : "no_url";
//   }
// };

// Primary strategies are simple boolean tests: is it rising? Is it falling?
const std::map<std::string, std::function<bool(cont)>> primary_strategies{

    {"crouching",
     [](cont p) {
       static_cast<void>(p);
       return true;
     }},

    {"rising",
     [](cont p) {
       unsigned int trend = 0;
       for (auto i = p.cbegin(); i != std::prev(p.cend()); ++i)
         if (*i < *std::next(i))
           ++trend;

       return trend > p.size() / 2;
     }},

    {"hidden",
     [](cont p) {
       unsigned int trend = 0;
       for (auto i = p.cbegin(); i != std::prev(p.cend()); ++i)
         if (*i > *std::next(i))
           ++trend;

       return trend > p.size() / 2;
     }},

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

// Secondary strategies yield a threshold
const std::map<std::string, func> strategies{

    {"hustle", [](cont p) { return p.front() / p.back(); }},
    {"forest", [](cont p) { return p.back() / p.front(); }},

    {"quill",
     [](cont p) {
       return std::accumulate(p.cbegin(), p.cend(), 0.0) / p.back();
     }},

    {"ken",
     [](cont p) {
       return p.back() / std::accumulate(p.cbegin(), p.cend(), 0.0);
     }},

    {"peppard",
     [](cont p) {
       return std::accumulate(p.cbegin(), p.cend(), 0.0) / p.front();
     }},

    {"owl",
     [](cont p) {
       return p.front() / std::accumulate(p.cbegin(), p.cend(), 0.0);
     }},

    {"terry",
     [](cont p) {
       const auto filt = p.size() / 2;
       return std::accumulate(p.cbegin(), std::prev(p.cend(), filt), 0.0) /
              std::accumulate(std::next(p.cbegin(), filt), p.cend(), 0.0);
     }},

    {"tibbs",
     [](cont p) {
       const auto filt = p.size() / 2;
       return std::accumulate(std::next(p.cbegin(), filt), p.cend(), 0.0) /
              std::accumulate(p.cbegin(), std::prev(p.cend(), filt), 0.0);
     }},

    {"crash",
     [](cont p) {
       const auto filt = p.size() / 2;
       return std::accumulate(std::next(p.cbegin(), filt), p.cend(), 0.0) /
              std::accumulate(p.cbegin(), p.cend(), 0.0);
     }},

    {"burn",
     [](cont p) {
       const auto filt = p.size() / 2;
       return std::accumulate(p.cbegin(), p.cend(), 0.0) /
              std::accumulate(std::next(p.cbegin(), filt), p.cend(), 0.0);
     }},

    {"cadiz",
     [](cont p) {
       const auto val =
           p.back() / *std::max_element(p.cbegin(), std::prev(p.cend()));
       return std::isinf(val) ? 0.0 : val;
     }},

    {"nacho",
     [](cont p) {
       return *std::max_element(p.cbegin(), std::prev(p.cend())) / p.back();
     }},

    {"robin",
     [](cont p) {
       return p.front() / *std::max_element(std::next(p.cbegin()), p.cend());
     }},

    {"cricket",
     [](cont p) {
       return *std::max_element(std::next(p.cbegin()), p.cend()) / p.front();
     }},

    {"biro",
     [](cont p) {
       return p.back() / *std::min_element(p.cbegin(), std::prev(p.cend()));
     }},

    {"pencil",
     [](cont p) {
       return *std::min_element(p.cbegin(), std::prev(p.cend())) / p.back();
     }},

    {"stride",
     [](cont p) {
       const auto min = *std::min_element(std::next(p.cbegin()), p.cend());
       return min > 0.0 ? p.front() / min : 0.0;
     }},

    {"stick",
     [](cont p) {
       return *std::min_element(std::next(p.cbegin()), p.cend()) / p.front();
     }},
};

// The sell strategy: return the index of the first price to exceed
// the sell threshold or return the end iterator
// using iter = const std::vector<double>::const_iterator &;
// const auto sell = [](iter current, iter future) {
//   return std::find_if(current, future,
//                       [spot = *current](const auto &future_price) {
//                         return future_price > spot * 1.05;
//                       });
// };

// Fetch all price files
struct trade {
  std::string from_symbol;
  std::string to_symbol;
  std::string exchange;

  // Stream in the trade info
  friend std::istream &operator>>(std::istream &is, trade &t) {
    is >> t.from_symbol >> t.to_symbol >> t.exchange;

    // Trim trailing asterisk
    if (t.from_symbol.back() == '*')
      t.from_symbol.pop_back();

    return is;
  }
};
} // namespace handt

int main() {

  // Create a set of thresholds to use with each buy strategy
  std::vector<int> thresholds(5);
  std::iota(thresholds.begin(), thresholds.end(), 2);

  // Create and initialise a container of all strategy permuations
  static std::vector<handt::strategy_combo> permutations;
  const auto total_permutations = handt::primary_strategies.size() *
                                  handt::strategies.size() * thresholds.size();
  permutations.reserve(total_permutations);

  // Populate with the strategy library
  for (const auto &[name1, buy1] : handt::primary_strategies)
    for (const auto &[name2, buy2] : handt::strategies)
      for (const auto &threshold : thresholds)
        permutations.push_back(
            {name1 + ' ' + name2 + ' ' + std::to_string(threshold), buy1, buy2,
             threshold});

  // for (const auto &s : permutations)
  //   std::puts(s.name.c_str());

  std::vector<std::string> currency_pairs;
  for (const auto &file : std::filesystem::directory_iterator("tmp"))
    currency_pairs.emplace_back(file.path());

  // Extract prices from each file
  for (const auto &file : currency_pairs) {

    std::cout << file << '\n';

    // Open prices and get the trade info
    std::ifstream in(file);
    handt::trade t;
    in >> t;

    struct strategy_performance {
      std::string name;
      unsigned int successful_trades = 0;
    };

    std::vector<strategy_performance> summary;

    // Get the prices and run the strategies over them
    if (const std::vector<double> prices{std::istream_iterator<double>(in), {}};
        !prices.empty()) {

      strategy_performance strategy;

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

        // Nudge the analysis window along
        std::advance(historic_price_index, 1);

        // Update upstream prices
        current_price_index = std::next(historic_price_index, analysis_window);
        future_price_index = std::next(current_price_index, sell_window);
      }
    }

#if 0
      for (auto &strategy : summary) {

            // Store the latest price
            strategy.spot = prices.back();
	    // const auto primary_buy = strategy.primary;
	    // const auto secondary_buy = strategy.secondary;
	    // const auto buy_threshold = strategy.threshold;

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
            auto future_price_index =
                std::next(current_price_index, sell_window);

            // Move windows along until we run out of prices
            // const double buy_threshold = 1.1;
            while (future_price_index < prices.cend()) {

              // Test strategy
              if (primary_buy({historic_price_index, current_price_index}) &&
                  secondary_buy({historic_price_index, current_price_index}) >
                      buy_threshold) {

                // Strategy triggered, so look ahead to see if it succeeded in
                // the defined trade window
                if (const auto sell_price_index =
                        handt::sell(current_price_index, future_price_index);
                    sell_price_index != future_price_index) {
                  ++strategy.good_deals;

                  // Move the analysis window so the next iteration starts at
                  // the last sell price
                  historic_price_index = sell_price_index;
                } else
                  ++strategy.bad_deals;
              }

              // Nudge the analysis window along
              std::advance(historic_price_index, 1);

              // Update upstream prices
              current_price_index =
                  std::next(historic_price_index, analysis_window);
              future_price_index = std::next(current_price_index, sell_window);

              // Track how many times we could have traded
              ++strategy.opportunities_to_trade;
            }

            // Calculate prospects using the most recent prices
            historic_price_index = std::prev(prices.cend(), analysis_window);
            current_price_index = prices.cend();

            if (strategy.trigger_ratio =
                    secondary_buy({historic_price_index, current_price_index});
                primary_buy({historic_price_index, current_price_index}) &&
                strategy.trigger_ratio > buy_threshold)
              strategy.current_prospect = true;
          }
    }

    }
#endif
  }

  // Sort strategies by effectiveness
  // std::sort(permutations.begin(), permutations.end(),
  //           [](const auto &a, const auto &b) {
  //             return (a.good_deals ? a.good_deals : 1.0) /
  //                        (a.bad_deals ? a.bad_deals : 1.0) >
  //                    (b.good_deals ? b.good_deals : 1.0) /
  //                        (b.bad_deals ? b.bad_deals : 1.0);
  //           });

  // Strategy and trade overview
  std::cout << currency_pairs.size() << " currency pairs, "
            << handt::primary_strategies.size() << " primary strategies, "
            << handt::strategies.size() << " secondary strategies, "
            << thresholds.size() << " thresholds, (" << permutations.size()
            << " strategy permutations.)\n\n";

  // Print strategy reports
  // std::puts(summary.front().heading().c_str());
  // for (const auto &s : summary)
  //   std::puts(s.str().c_str());
}
