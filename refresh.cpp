#include "handt.h"
#include <algorithm>
#include <iostream>
#include <sstream>
// #include <type_traits>

int main() {

  // Configure debug
  std::stringstream out;
  out.precision(10);
  out << std::boolalpha;

  // Get recent prices (not necessarily for all positions)
  const auto prices = handt::get_prices();

  // Get current positions (not necessarily for all prices)
  const auto positions = handt::get_positions();

  auto find_prices = [&prices](const std::string symbol) {
    const auto it =
        std::find_if(prices.cbegin(), prices.cend(),
                     [symbol](const auto p) { return p.first == symbol; });
    return it != prices.cend() ? it->second : std::vector<double>();
  };

  // Update positions
  std::decay_t<decltype(positions)> update;
  std::transform(positions.cbegin(), positions.cend(),
                 std::back_inserter(update),
                 [&find_prices, &out](const auto p) {

                   // Create a copy of the position
                   std::decay_t<decltype(p)> pos = p;

                   // If we've found some prices then update the position and
                   // return it
                   const auto q = find_prices(p.symbol);
                   if (!q.empty()) {
                     pos.sell_price = q.back();
                     pos.notes = "refreshd";
                   }

                   return pos;
                 });

  for (const auto position : update)
    out << position << "\n";

  std::cout << out.str();
}
