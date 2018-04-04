#include "handt.h"
#include <iostream>

int main() {

  std::stringstream out;

  // Get current timestamp
  const auto timestamp = handt::get_timestamp();
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

      // Otherwise check if it's ready to cash in
      else if (position.yield() > 1.06)
          position.open = false;
    }

    out << position << "\n";
  }

  std::cout << out.str();
}
