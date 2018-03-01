#include "utils.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <type_traits>

int main() {

  // Configure debug
  std::stringstream out;
  out.precision(10);

  // Get recent prices (not necessarily for all positions)
  const auto prices = get_prices();

  // Get current positions (not necessarily for all prices)
  const auto positions = get_positions();

  // Update positions
  std::decay_t<decltype(positions)> updated;
  std::transform(positions.cbegin(), positions.cend(),
                 std::back_inserter(updated), [](const auto &p){
                    return p;
                 });

  // Print
  out << prices.size() << " prices\n";
  out << positions.size() << " original positions\n";
  out << updated.size() << " updated positions\n";
  std::cout << out.str();
}
