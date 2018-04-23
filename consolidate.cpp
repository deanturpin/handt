#include "handt.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <type_traits>
#include <vector>

int main() {

  // Configure debug
  std::stringstream out;

  const auto &reviewed_positions = handt::get_purged_positions();

  // Store new positions in a separate container
  std::decay_t<decltype(reviewed_positions)> new_positions;

  // Iterate over each new prospect to check we don't already hold a position
  for (const auto &prospect : handt::get_prospects()) {
    for (const auto &strategy : prospect.strategies) {

      // Check if we already hold an open position with this currency/strategy
      const auto symbol = prospect.symbol;
      const auto it = std::find_if(
          reviewed_positions.cbegin(), reviewed_positions.cend(),
          [&symbol, &strategy](const auto p) {
            return p.open && p.symbol == symbol && p.strategy == strategy;
          });

      // Create a position if we don't already hold one
      if (it == reviewed_positions.cend()) {

        // Initialise position with prospect details and store it
        handt::position position;
        position.symbol = prospect.symbol;
        position.strategy = strategy;
        position.buy_price = position.sell_price = prospect.spot;
        new_positions.push_back(position);
      }
    }
  }

  // Print all positions
  for (const auto &p : {reviewed_positions, new_positions})
    for (const auto &q : p)
      out << q << "\n";

  std::cout << out.str();
}
