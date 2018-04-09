#include "handt.h"
#include <iostream>

int main() {

  std::stringstream out;

  const auto timestamp = handt::get_timestamp();

  // Review each position
  for (auto &position : handt::get_refreshed_positions()) {

    // Mark old position for deletion
    if (timestamp - position.timestamp > (60 * 60 * 24)) {
      position.status = "time_out";
      position.open = false;
    }

    // Check if it's ready to cash in
    else if (position.yield() > handt::sell_threshold) {
      position.status = "cashfome";
      position.open = false;
    }

    // Cut our losses
    else if (position.yield() < handt::cut_losses_threshold) {
      position.status = "cutropes";
      position.open = false;
    }

    out << position << "\n";
  }

  std::cout << out.str();
}
