#include "handt.h"
#include <iostream>

int main() {

  // Configure debug
  std::stringstream out;
  out.precision(10);
  out << std::boolalpha;

  // Get current refreshed positions
  auto positions = handt::get_refreshed_positions();

  // Close any positions that have matured sufficiently
  for (auto &p : positions)
    if (p.buy_price > 0)
      if (p.sell_price / p.buy_price > 1.10)
        p.open = false;

  // Print all positions
  out << "# " << positions.size() << " positions\n";
  for (const auto position : positions)
    out << position << "\n";

  std::cout << out.str();
}
