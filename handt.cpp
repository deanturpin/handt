#include <algorithm>
#include <assert.h>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>
#include <vector>

namespace handt {

// The container passed throughout
using cont = const std::vector<double> &;

// Function definitions for the strategy types
using func1 = std::function<bool(cont)>;
using func2 = std::function<double(cont)>;

// Primary strategies are simple boolean tests
const std::vector<std::pair<std::string, func1>> primary_strategies{

    // Always return positively
    {"Crouching", []([[maybe_unused]] cont p) { return true; }},

    // Return positively if trending upwards
    {"Leaping",
     [](cont p) {
       unsigned int trend = 0;
       for (auto i = p.cbegin(); i != std::prev(p.cend()); ++i)
         if (*i < *std::next(i))
           ++trend;

       return trend > p.size() / 2;
     }},

    // Return positively if trending downwards
    {"Supine",
     [](cont p) {
       unsigned int trend = 0;
       for (auto i = p.cbegin(); i != std::prev(p.cend()); ++i)
         if (*i > *std::next(i))
           ++trend;

       return trend > p.size() / 2;
     }},

    // Return positively if crossing a significant boundary
    {"Straddling",
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

    // Minimum comes before maximum
    {"Darting",
     [](cont p) {
       const auto &[min, max] = std::minmax_element(p.cbegin(), p.cend());
       return std::distance(p.cbegin(), min) < std::distance(p.cbegin(), max);
     }},

    // Maximum comes before minimum
    {"Slouching",
     [](cont p) {
       const auto &[min, max] = std::minmax_element(p.cbegin(), p.cend());
       return std::distance(p.cbegin(), min) > std::distance(p.cbegin(), max);
     }},
};

// Strategy definition helper routines
const auto mean = [](const auto &p) {
  return std::accumulate(p.cbegin(), p.cend(), 0.0) /
         static_cast<double>(p.size());
};

const auto maximum = [](const auto &p) {
  return *std::max_element(p.cbegin(), p.cend());
};

const auto minimum = [](const auto &p) {
  return *std::min_element(p.cbegin(), p.cend());
};

const auto front_end = [](const auto &p) {
  return decltype(p){p.cbegin(), std::prev(p.cend(), p.size() / 2)};
};

const auto back_end = [](const auto &p) {
  return decltype(p){std::next(p.cbegin(), p.size() / 2), p.cend()};
};

const auto front = [](const auto &p) { return p.front(); };
const auto back = [](const auto &p) { return p.back(); };

// Secondary strategies yield a buy threshold
const std::vector<std::pair<std::string, func2>> secondary_strategies{

    // Always succeed
    {"Lundehund", []([[maybe_unused]] cont p) { return 2.0; }},

    // Front/back
    {"Norrbottenspets", [](cont p) { return front(p) / back(p); }},
    {"Jagdterrier", [](cont p) { return back(p) / front(p); }},

    // Mean over front/back
    {"Xoloitzcuintli", [](cont p) { return mean(p) / back(p); }},
    {"Basenji", [](cont p) { return mean(p) / front(p); }},
    {"Sphynx", [](cont p) { return front(p) / mean(p); }},
    {"Affenpinscher", [](cont p) { return back(p) / mean(p); }},

    // Partial means
    {"Capybara", [](cont p) { return mean(front_end(p)) / mean(back_end(p)); }},
    {"Munchkin", [](cont p) { return mean(back_end(p)) / mean(front_end(p)); }},
    {"Badger", [](cont p) { return mean(p) / mean(back_end(p)); }},
    {"Bandicoot", [](cont p) { return mean(back_end(p)) / mean(p); }},

    // Min/max over back/front
    {"Mink", [](cont p) { return minimum(p) / back(p); }},
    {"Ocelot", [](cont p) { return minimum(p) / front(p); }},
    {"Griffon", [](cont p) { return maximum(p) / back(p); }},
    {"Cricket", [](cont p) { return maximum(p) / front(p); }},

    // Back/front over min/max
    {"Axolotl", [](cont p) { return back(p) / minimum(p); }},
    {"Shiba Inu", [](cont p) { return front(p) / minimum(p); }},
    {"Lowchen", [](cont p) { return back(p) / maximum(p); }},
    {"Narwahl", [](cont p) { return front(p) / maximum(p); }},

    // Min over max
    {"Bichon Frise", [](cont p) { return minimum(p) / maximum(p); }},
    {"Havanese", [](cont p) { return maximum(p) / minimum(p); }},

    // Min/max over mean
    {"Shih Tzu", [](cont p) { return minimum(p) / mean(p); }},
    {"Pomeranian", [](cont p) { return maximum(p) / mean(p); }},
    {"Pekingese", [](cont p) { return mean(p) / minimum(p); }},
    {"Papillon", [](cont p) { return mean(p) / maximum(p); }},
};

} // namespace handt

int main() {

  // Unit test
  assert(handt::maximum(std::vector<double>{3, 4, 5}) > 4.0);
  assert(handt::minimum(std::vector<double>{3, 4, 5}) < 4.0);

  // Create a set of thresholds to use with each buy strategy
  std::vector<int> thresholds(25);
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

      // Check we haven't ended up with a huge number by inadvertantly dividing
      // a double with a very similar double, and then return strategy success
      return !std::isinf(secondary_response) && primary_response &&
             secondary_response > ratio;
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

  // Fetch list of price files
  std::vector<std::string> currency_pairs;
  for (const auto &file : std::filesystem::directory_iterator("tmp"))
    currency_pairs.emplace_back(file.path());

  // Structure to capture the results during a strategy backtest
  struct strategy_performance {
    std::string name;
    std::string from_symbol;
    std::string to_symbol;
    std::string exchange;
    double spot = 0.0;
    unsigned int good_deals = 0;
    unsigned int bad_deals = 0;
    unsigned int opportunities = 0;
    bool buy = false;
  };

  // Create container for final strategy report
  std::list<strategy_performance> performance;

  // Extract prices from each file
  for (const auto &file : currency_pairs) {

    // Open prices and get the trade info
    std::ifstream in(file);
    std::string from_symbol, to_symbol, exchange;
    in >> from_symbol >> to_symbol >> exchange;

    // Get the prices and run the strategies over them
    const std::vector<double> prices{std::istream_iterator<double>(in), {}};

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

  // Sort strategies by performance
  performance.sort([](const auto &a, const auto &b) {
    // We don't want to divide by zero be also want zero denominators or
    // numerators to sort nicely
    return static_cast<double>(a.good_deals ? a.good_deals : .9) /
               (a.bad_deals ? a.bad_deals : .9) >
           static_cast<double>(b.good_deals ? b.good_deals : .9) /
               (b.bad_deals ? b.bad_deals : .9);
  });

  // Calculate total tests performed during backtesting
  const auto tests_performed = std::accumulate(
      performance.cbegin(), performance.cend(), 0ul,
      [](unsigned int sum, const auto &p) { return sum + p.opportunities; });

  // Pretty print large numbers
  std::cout.imbue(std::locale(""));

  // Strategy and trade overview
  std::cout << "* " << currency_pairs.size() << " currency pairs\n"
            << "* " << permutations.size() << " strategies\n"
            << "* " << performance.size() << " strategy/pair combinations\n"
            << "* " << tests_performed << " backtests\n\n";

  // Report individual strategy performance
  std::cout << "# Current prospects (" << sell_threshold
            << " % return)\n"
               "Prospects based on prices from the last 24 hours.\n\n"
               "Strategy|Pair|Good/Bad|Spot\n"
               "---|---|---|---\n";

  unsigned int buy_count = 0;
  for (const auto &s : performance)
    if (s.buy) {
      // Trim any trailing asterisk from symbol name
      std::string_view from_symbol_trimmed = s.from_symbol;
      if (from_symbol_trimmed.back() == '*')
        from_symbol_trimmed.remove_suffix(1);

      // Construct exchange URL
      const std::string url =
          "https://" +
          (s.exchange == std::string("Coinbase")
               ? "coinbase.com"
               : s.exchange == std::string("Binance")
                     ? "binance.com/en/trade/" +
                           std::string(from_symbol_trimmed) + '_' + s.to_symbol
                     : "no_url");

      // Report strategy summary
      std::cout << s.name << '|' << "[" << s.from_symbol << '-' << s.to_symbol
                << "](" << url << ")|" << s.good_deals << '/' << s.bad_deals
                << '|' << s.spot << '\n';

      ++buy_count;

      if (buy_count > 10)
        break;
    }

  // Report individual strategy performance
  std::cout << R"(
# Top performers
The results are ordered by success which is measured using the proportion of
good to bad trades.

Strategy|Pair|Good/Bad|Spot
---|---|---|---
)";

  for (const auto &s : performance) {

    // Trim any trailing asterisk from symbol name
    std::string_view from_symbol_trimmed = s.from_symbol;
    if (from_symbol_trimmed.back() == '*')
      from_symbol_trimmed.remove_suffix(1);

    // Construct exchange URL
    const std::string url =
        "https://" +
        (s.exchange == std::string("Coinbase")
             ? "coinbase.com"
             : s.exchange == std::string("Binance")
                   ? "binance.com/en/trade/" +
                         std::string(from_symbol_trimmed) + '_' + s.to_symbol
                   : "no_url");

    // Report strategy summary
    std::cout << s.name << '|' << "[" << s.from_symbol << '-' << s.to_symbol
              << "](" << url << ")|" << s.good_deals << '/' << s.bad_deals
              << '|' << s.spot << '\n';
  }
}
