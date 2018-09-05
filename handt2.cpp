#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

// A currency pair is a duo of symbols and an exchange whence the price came
struct currency_pair {
  std::string from_sym{};
  std::string to_sym{};
  std::string exchange{};
};

std::vector<currency_pair> get_pairs() {

  currency_pair p;

  // Extract and store the portfolio of currency pairs
  std::vector<currency_pair> pairs;
  std::ifstream in("pairs2.csv");
  while (in >> p.from_sym >> p.to_sym >> p.exchange)
    pairs.emplace_back(p);

  return pairs;
}

int main() {

  // Fetch the pairs we're interested in
  const auto &pairs = get_pairs();
  std::cout << pairs.size() << " pairs read\n";

  // Get prices
  for (auto &file : std::filesystem::directory_iterator("tmp")) {

    // Get the trade params
    std::ifstream in(file.path());
    if (currency_pair p; in >> p.from_sym >> p.to_sym >> p.exchange)
      std::cout << "Processing " << p.from_sym << " from symbol\n";

    // Get the prices
    const std::vector<double> prices{std::istream_iterator<double>(in), {}};

    if (!prices.empty()) {

      std::cout << prices.size() << " prices read\n";

      // Backtest
      std::cout << std::accumulate(prices.cbegin(), prices.cend(), 0.0) /
                       prices.size()
                << " average price\n";

      // Configure trading period
      const unsigned int analysis_window = 24;
      const unsigned int sell_window     = analysis_window * 2;

      // Set up some indices into the prices
      auto earliest_price = prices.cbegin();
      auto latest_price   = std::next(earliest_price, analysis_window);
      auto future_price   = std::next(latest_price, sell_window);

      // Stat reporting
      unsigned int successes              = 0;
      unsigned int fails                  = 0;
      unsigned int opportunities_to_trade = 0;

      while (future_price < prices.cend()) {

        const double buy_threshold  = 1.2;
        const double sell_threshold = 1.02;

        // Check if we're ready to trade
        if (*earliest_price / *latest_price > buy_threshold) {

          // Find the first opportunity to sell in the future sell window
          const auto max_price = std::max_element(latest_price, future_price);

          // Look ahead to see if we would have cashed in the trade
          if (*max_price / *latest_price > sell_threshold) {
            ++successes;

            // Move the trade window to the first opportunity to sell
            earliest_price = max_price;
          }

        } else
          ++fails;

        std::advance(earliest_price, 1);

        latest_price = std::next(earliest_price, analysis_window);
        future_price = std::next(latest_price, sell_window);

        ++opportunities_to_trade;
      }

      std::cout << successes << " successes\n";
      std::cout << fails << " fails\n";
      std::cout << opportunities_to_trade << " opportunities to trade\n";

      std::cout << 100.0 * successes / fails << " % success rate\n";
    }
  }
}
