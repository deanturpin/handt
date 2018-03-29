#include "handt.h"
#include "low_frequency_trader.h"
#include <iostream>
#include <sstream>
#include <vector>

int main() {

  // Configure debug
  std::stringstream out;
  out.precision(10);
  out << "# prospects\n";

  // Test strategies on each series
  for (const auto &p : handt::get_prices())
    if (!p.series.empty()) {

      const auto spot = p.series.back();
      const auto &buys = lft::run_strategies(p.series);

      // If some strategies have triggered then print them
      if (!buys.empty()) {
        out << p.symbol << "\t" << spot << " ";
        for (const auto &buy : buys)
          out << buy << " ";
        out << "\n";
      }
    }

  std::cout << out.str();
}
