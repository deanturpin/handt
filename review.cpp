#include "handt.h"
#include <iostream>

int main() {

  // Configure debug
  std::stringstream out;
  out.precision(10);
  out << std::boolalpha;

  // Review each position
  for (auto &position : handt::get_refreshed_positions()) {

    // Close position if sufficiently matured
    if (position.open)
      if (position.buy_price > 0)
        if (position.sell_price / position.buy_price > 1.10)
          position.open = false;

    out << position << "\n";
  }

  std::cout << out.str();
}
