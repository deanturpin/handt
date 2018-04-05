#include "handt.h"
#include <iostream>

int main() {

  std::stringstream out;

  const auto timestamp = handt::get_timestamp();

  // Review each position
  for (auto &position : handt::get_refreshed_positions()) {

    // Mark old position for deletion
    if (timestamp - position.timestamp > (60 * 60 * 24)) {
      position.status = "purgenow";
      position.open = false;
    }

    // Check if it's ready to cash in
    else if (position.yield() > 1.06) {
      position.status = "cashmein";
      position.open = false;
    }

    // Cut our losses
    else if (position.yield() < .8) {
      position.status = "cutropes";
      position.open = false;
    }

    out << position << "\n";
  }

  out << "# " << timestamp << " seconds since epoch\n";

  std::cout << out.str();
}
