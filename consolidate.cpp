#include "include/handt.h"
#include <algorithm>
#include <iostream>
#include <type_traits>

int main() {
  // Get current positions and create a container for any new positions
  const auto &purged_positions = handt::get_purged_positions();
  std::decay_t<decltype(purged_positions)> new_positions;

  // Iterate over each new prospect to check we don't already hold a position
  for (const auto &prospect : handt::get_prospects()) {
    for (const auto &strategy : prospect.strategies) {
      // Check if we already hold an open position with this currency/strategy
      const auto symbol = prospect.symbol;
      const auto it = std::find_if(
          purged_positions.cbegin(), purged_positions.cend(),
          [&symbol, &strategy](const auto p) {
            return p.open && p.symbol == symbol && p.strategy == strategy;
          });

      // Create a position if we don't already hold one
      if (it == purged_positions.cend()) {
        // Initialise position with prospect details and store it
        handt::position position;
        position.symbol = prospect.symbol;
        position.strategy = strategy;
        position.buy_price = position.sell_price = prospect.spot;
        new_positions.emplace_back(position);
      }
    }
  }

  // Print all positions
  for (const auto &p : {purged_positions, new_positions})
    for (const auto &q : p)
      std::cout << q << '\n';
}
