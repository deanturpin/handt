#include "handt.h"
#include <iostream>

int main() {

  // Configure debug
  std::stringstream out;
  out.precision(10);
  out << std::boolalpha;

  // Get current timestamp
  const auto timestamp = handt::seconds_since_epoch();
  out << "# " << timestamp << " timestamp\n";

  // Review each position
  for (auto &position : handt::get_refreshed_positions()) {

    // Close position if sufficiently matured
    if (position.open) {

      // Mark old position for deletion
      if (timestamp - position.timestamp > (60 * 60 * 24)) {
        position.open = false;
        position.status = "purgenow";
      }

      // Otherwise check if it's mature
      else if (position.buy_price > 0)
        if (position.sell_price / position.buy_price > 1.10)
          position.open = false;
    }

    out << position << "\n";
  }

  std::cout << out.str();
}
