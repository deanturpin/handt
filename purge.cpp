#include "include/handt.h"
#include <algorithm>
#include <iostream>

int main() {

  // Get all positions
  const auto &reviewed_positions = handt::get_reviewed_positions();

  // Filter closed positions
  std::decay_t<decltype(reviewed_positions)> open_positions;
  std::copy_if(std::cbegin(reviewed_positions), std::cend(reviewed_positions),
               std::back_inserter(open_positions),
               [](const auto &position) { return position.open; });

  // Print remaining positions
  for (const auto &position : open_positions)
    std::cout << position << '\n';

  std::cout << "# " << reviewed_positions.size() << " reviewed positions\n";
  std::cout << "# " << open_positions.size() << " open positions\n";
}
