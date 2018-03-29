#include "handt.h"
#include "strategy.h"
#include <functional>
#include <vector>
#include <sstream>
#include <iostream>

// Return a list of the strategy names that reported "buy" for the series of
// prices given
vector<string> run_strategies(series s) {

  using library = const vector<std::function<result(series, param)>>;

  // Strategies that take thresholds (in percent)
  const vector<double> thresholds{10.0};
  library lib1{flicking_down, flicking_up,     ski_jumping,
               stepping_up,   stepping_down,   steady_rising,
               kosovich,      rolling_average, random_decision};

  vector<string> trades;
  for (const auto &buy : lib1)
    for (const auto &t : thresholds) {
      const auto b = buy(s, t);

      if (b.second)
        trades.push_back(b.first);
    }

  // Strategies that take ratios
  const vector<double> ratios{2.0};
  library lib2{average_compare, average_inter};

  for (const auto &buy : lib2)
    for (const auto &r : ratios) {
      const auto b = buy(s, r);

      if (b.second)
        trades.push_back(b.first);
    }

  return trades;
}

int main() {

  // Get some prices
  const auto prices = handt::get_prices();

  // A place for the results
  std::stringstream out;
  out.precision(10);
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
