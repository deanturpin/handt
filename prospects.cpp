#include "handt.h"
#include "low_frequency_trader.h"
#include <functional>
#include <iostream>
#include <sstream>
#include <vector>

// Return a list of the strategy names that reported "buy" for the series of
// prices given
std::vector<std::string> run_strategies(lft::series s) {

  using namespace lft;
  using library = const std::vector<std::function<result(series, param)>>;

  // Strategies that take thresholds (in percent)
  library lib1{flicking_down, flicking_up,     ski_jumping,
               stepping_up,   stepping_down,   steady_rising,
               kosovich,      rolling_average, random_decision};

  std::vector<string> trades;
  for (const auto &buy : lib1) {
    const auto b = buy(s, 10.0);
    if (b.second)
      trades.push_back(b.first);
  }

  // Strategies that take ratios
  library lib2{average_compare, average_inter};

  for (const auto &buy : lib2) {
    const auto b = buy(s, 2.0);
    if (b.second)
      trades.push_back(b.first);
  }

  return trades;
}

int main() {

  // Configure debug
  std::stringstream out;
  out.precision(10);

  // Get some prices
  const auto prices = handt::get_prices();
  out << "# prospects\n";
  out << "# " << prices.size() << " prices\n";

  // Test strategies on each series
  for (const auto &p : prices) {

    const auto &name = p.first;
    const auto &series = p.second;

    if (!series.empty()) {
      const auto spot = series.back();
      const auto buys = run_strategies(series);
      if (!buys.empty()) {
        out << name << "\t" << spot << " ";
        for (const auto &buy : buys)
          out << buy << " ";
        out << "\n";
      }
    }
  }

  std::cout << out.str();
}
