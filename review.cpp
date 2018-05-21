#include "include/handt.h"
#include <vector>

using positions = std::vector<handt::position>;

// Review open positions and return an updated list with statuses updated
positions review(const positions &open, const unsigned long &timestamp,
                 const double &sell_threshold,
                 const double &cut_losses_threshold) {

  // Create a container to store the reviewed positions
  positions reviewed;

  // Review each open position
  for (const auto &p : open) {

    // Create a copy of the position
    auto position = p;

    // Mark old position for deletion if it has expired
    if (timestamp - position.timestamp > (60 * 60 * 24)) {
      position.status = "time_out";
      position.open = false;
    }

    // Or check if it's ready to cash in
    else if (position.yield() > sell_threshold)
    {
      position.status = "maturity";
      position.open = false;
    }

    // Or cut our losses
    else if (position.yield() < cut_losses_threshold) {
      position.status = "cut_loss";
      position.open = false;
    }

    // Store updated position
    reviewed.push_back( position );
  }

  return reviewed;
}

#include <iostream>

int main() {

  // Get refreshed positions and review
  const auto &reviewed =
      review(handt::get_refreshed_positions(), handt::get_timestamp(),
             handt::sell_threshold, handt::cut_losses_threshold);

  // Print reviewed positions
  for (const auto &position : reviewed)
    std::cout << position << '\n';
}
