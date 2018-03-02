#include "utils.h"
#include <algorithm>
#include <iostream>
#include <sstream>
// #include <type_traits>

int main() {

  // Configure debug
  std::stringstream out;
  out.precision(10);
  out << std::boolalpha;

  // Get current positions (not necessarily for all prices)
  auto positions = get_positions("refresh.csv");

  // Close any positions
  for (auto &p : positions)
    if (p.buy_price > 0)
      if (p.sell_price / p.buy_price > 1.10)
        p.open = false;

  for (const auto position : positions)
    out << position << "\n";

  std::cout << out.str();
}
