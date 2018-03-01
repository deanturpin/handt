#include "utils.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <type_traits>

int main() {

  // Configure debug
  std::stringstream out;
  out.precision(10);
  out << std::boolalpha;

  // Get current positions (not necessarily for all prices)
  const auto positions = get_positions("refresh.csv");

  // out << positions.size() << " reviewed positions\n";

  // Close any positions
  for (auto p : positions)
    if (p.sell_price / p.buy_price > 1.1)
      p.open = false;

  for (const auto p : positions)
    out << p;

  std::cout << out.str();
}
