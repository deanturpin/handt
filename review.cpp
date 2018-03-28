#include "handt.h"
#include <algorithm>
#include <iostream>
#include <sstream>

int main() {

  // Configure debug
  std::stringstream out;
  out.precision(10);
  out << std::boolalpha;

  // Get current refreshed positions
  auto positions = handt::get_positions("refresh.csv");

  // Close any positions that have matured sufficiently
  for (auto &p : positions)
    if (p.buy_price > 0)
      if (p.sell_price / p.buy_price > 1.10)
        p.open = false;

  for (const auto position : positions)
    out << position << "\n";

  out << "# " << positions.size() << " positions\n";

  std::cout << out.str();
}
