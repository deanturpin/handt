#include <algorithm>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iterator>
#include <map>
#include <numeric>
#include <vector>

int main() {

  // Structure to represent a trade
  struct strategy_summary {
    std::string from_symbol = "undefined";
    std::string to_symbol = "undefined";
    std::string exchange = "undefined";
    std::string strategy_name = "undefined";
    unsigned int opportunities_to_trade = 0u;
    unsigned int good_deals = 0u;
    unsigned int bad_deals = 0u;
    double average_price = 0u;
    bool current_prospect = false;
    double trigger_ratio = 0.0;

    std::string str() const {
      std::stringstream out;
      out << strategy_name << '\t' << from_symbol << '-' << to_symbol << ' '
          << exchange << ' ' << good_deals << '/' << bad_deals << ' '
          << average_price << ' ' << opportunities_to_trade << " opps "
          << trigger_ratio << (current_prospect ? " *" : "");

      return out.str();
    }
  };

  // Create a container for all trades
  static std::vector<strategy_summary> summary;

  // Get prices
  for (const auto &file : std::filesystem::directory_iterator("tmp")) {

    // Define the buy strategies, eash strategy function takes a pair of
    // iterators that define a window into the prices: the analysis window
    using cont = const std::vector<double>;
    using func = std::function<double(cont)>;

    const std::map<std::string, func> strategies{

        // First and last comparisons
        {"nao", [](cont p) { return p.front() / p.back(); }},
        {"oan", [](cont p) { return p.back() / p.front(); }},

        // Averages
        {"dean",
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

        {"pig",
         [](cont p) {
           return p.front() / std::accumulate(p.cbegin(), p.cend(), 0.0);
         }},

        {"terry",
         [](cont p) {
           const auto filter_size = p.size() / 2;

           return std::accumulate(p.cbegin(), std::prev(p.cend(), filter_size),
                                  0.0) /
                  std::accumulate(std::next(p.cbegin(), filter_size), p.cend(),
                                  0.0);
         }},

        {"tibbs",
         [](cont p) {
           const auto filter_size = p.size() / 2;

           return std::accumulate(std::next(p.cbegin(), filter_size), p.cend(),
                                  0.0) /
                  std::accumulate(p.cbegin(), std::prev(p.cend(), filter_size),
                                  0.0);
         }},

        // Peak finders
        {"les",
         [](cont p) {
           return p.back() / *std::max_element(p.cbegin(), std::prev(p.cend()));
         }},

        {"nacho",
         [](cont p) {
           return *std::max_element(p.cbegin(), std::prev(p.cend())) / p.back();
         }},

        // Straddlers
        {"brian",
         [](cont p) {
           const auto max = std::max(p.front(), p.back());
           const auto min = std::min(p.front(), p.back());

           unsigned long threshold = 0;
           for (const unsigned long &mod : {1, 10, 100, 1000, 10000}) {

             const unsigned long test =
                 max - (static_cast<unsigned long>(max) % mod);

             if (test == 0)
               break;

             threshold = test;
           }

           return (min < threshold && max > threshold)
                      ? p.back() / std::accumulate(p.cbegin(), p.cend(), 0.0)
                      : 0.0;
         }},

        {"percy",
         [](cont p) {
           const auto max = std::max(p.front(), p.back());
           const auto min = std::min(p.front(), p.back());

           unsigned long threshold = 0;
           for (const unsigned long &mod : {1, 10, 100, 1000, 10000}) {

             const unsigned long test =
                 max - (static_cast<unsigned long>(max) % mod);

             if (test == 0)
               break;

             threshold = test;
           }

           return (min < threshold && max > threshold) ? p.back() / p.front()
                                                       : 0.0;
         }},

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
      for (const auto &[name, buy] : strategies) {

        // Create a new strategy summary, initialised with basic trade info
        strategy_summary &strategy = summary.emplace_back(
            strategy_summary{from_symbol, to_symbol, exchange, name});

        strategy.average_price =
            std::accumulate(prices.cbegin(), prices.cend(), 0.0) /
            prices.size();

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
        auto historic_price = prices.cbegin();
        auto current_price = std::next(historic_price, analysis_window);
        auto future_price = std::next(current_price, sell_window);

        // Move windows along until we run out of prices
        const double buy_threshold = 1.2;
        while (future_price < prices.cend()) {

          // The sell strategy: return the index of the first price to exceed
          // the sell threshold or return the end iterator
          using iter = const std::vector<double>::const_iterator &;
          const auto sell_strategy = [](iter current, iter future) {
            return std::find_if(current, future, [&current](const auto &p) {
              return p > *current * 1.05;
            });
          };

          // Test strategy
          if (buy({historic_price, current_price}) > buy_threshold) {

            // Strategy triggered, so look ahead to see if it succeeded in the
            // defined trade window
            if (const auto sell_price =
                    sell_strategy(current_price, future_price);
                sell_price != future_price) {
              ++strategy.good_deals;

              // Move the analysis window so the next iteration starts at the
              // last sell price
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

        // Calculate prospects using the most recent prices
        historic_price = std::prev(prices.cbegin(), analysis_window);
        current_price = prices.cend();

        if (strategy.trigger_ratio = buy({historic_price, current_price});
            strategy.trigger_ratio > buy_threshold)
          strategy.current_prospect = true;
      }
    }
  }

  // Sort strategies by effectiveness
  std::sort(summary.begin(), summary.end(), [](const auto &a, const auto &b) {
    return (a.good_deals ? a.good_deals : 1.0) /
               (a.bad_deals ? a.bad_deals : 1.0) >
           (b.good_deals ? b.good_deals : 1.0) /
               (b.bad_deals ? b.bad_deals : 1.0);
  });

  // Print overview
  std::stringstream totals;
  totals << summary.size() << " pair/strategy combinations tested\n";
  std::puts(totals.str().c_str());

  // Print strategy reports
  for (const auto &s : summary)
    std::puts(s.str().c_str());
}
