#include "include/handt.h"
#include "include/strategy.h"
#include <iostream>
#include <sstream>
#include <vector>

int main() {

  std::stringstream out;

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
