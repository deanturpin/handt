#include "include/handt.h"
#include "include/strategy.h"
#include <iostream>
#include <vector>

int main() {

  // Test strategies on each series
  for (const auto &p : handt::get_prices())
    if (!p.series.empty()) {

      const auto spot = p.series.back();
      const auto &buys = strategy::library(p.series);

      // If some strategies have triggered then print them
      if (!buys.empty()) {
        std::cout << p.symbol << '\t' << spot << ' ';
        for (const auto &buy : buys)
          std::cout << buy << ' ';
        std::cout << '\n';
      }
    }
}
