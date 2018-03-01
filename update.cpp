#include "utils.h"
#include <iostream>
#include <sstream>
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
  for (const auto &p : positions) {
    const auto name = p.name;
    const auto spot = p.sell_price;
    const auto strategy = p.strategy;
    out << name << "\t" << spot << "\t" << strategy << "\n";
    updated.push_back(p);
  }

  // Print
  out << prices.size() << " prices\n";
  out << positions.size() << " original positions\n";
  out << updated.size() << " updated positions\n";
  std::cout << out.str();
}
