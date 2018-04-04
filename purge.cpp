#include "handt.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main() {

  // Get all positions
  const auto &reviewed_positions = handt::get_reviewed_positions();

  // Filter closed positions
  std::decay_t<decltype(reviewed_positions)> purged_positions;
  std::copy_if(reviewed_positions.cbegin(), reviewed_positions.cend(),
               std::back_inserter(purged_positions),
               [](const auto &position) { return position.open; });

  // Print remaining positions
  std::stringstream out;
  for (const auto &position : purged_positions)
    out << position << '\n';

  out << "# " << reviewed_positions.size() << " reviewed positions\n";
  out << "# " << purged_positions.size() << " purged positions\n";
  std::cout << out.str();
}
