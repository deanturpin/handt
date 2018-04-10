#include "handt.h"

std::vector<handt::position>
review(const std::vector<handt::position> &positions) {

  // Create a container to store the review positions
  std::vector<handt::position> reviewed;

  // Review each position
  for (const auto &p : positions) {

    // Create a copy of the position
    handt::position position(p);

    // Mark old position for deletion if it has expired
    if (handt::get_timestamp() - position.timestamp > (60 * 60 * 24)) {
      position.status = "time_out";
      position.open = false;
    }

    // Or check if it's ready to cash in
    else if (position.yield() > handt::sell_threshold) {
      position.status = "cashfome";
      position.open = false;
    }

    // Or cut our losses
    else if (position.yield() < handt::cut_losses_threshold) {
      position.status = "cutropes";
      position.open = false;
    }

    // Store updated position
    reviewed.push_back(position);
  }

  return reviewed;
}

#include <iostream>

int main() {

  // Get latest positions
  const auto &positions = handt::get_refreshed_positions();

  // Dump review positions
  for (const auto &position : review(positions))
    std::cout << position << '\n';
}
