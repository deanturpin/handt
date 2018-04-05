#include "handt.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main() {

  // Get all positions
  const auto &reviewed_positions = handt::get_reviewed_positions();

  // Filter closed positions
  std::decay_t<decltype(reviewed_positions)> open_positions;
  std::copy_if(reviewed_positions.cbegin(), reviewed_positions.cend(),
               std::back_inserter(open_positions),
               [](const auto &position) { return position.open; });

  // Print remaining positions
  std::stringstream out;
  for (const auto &position : open_positions)
    out << position << '\n';

  out << "# " << reviewed_positions.size() << " reviewed positions\n";
  out << "# " << open_positions.size() << " open positions\n";
  std::cout << out.str();
}
