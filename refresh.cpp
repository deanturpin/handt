#include "include/handt.h"
#include <algorithm>
#include <iostream>

int main() {

  // Get recent prices
  const auto &prices = handt::get_prices();

  // Get current positions
  const auto &positions = handt::get_positions();

  // Lambda to search for a symbol in the recent prices
  const auto find_prices = [&prices](const std::string symbol) {
    const auto it =
        std::find_if(prices.cbegin(), prices.cend(),
                     [symbol](const auto p) { return p.symbol == symbol; });
    return it != prices.cend() ? it->series : std::vector<double>();
  };

  // Copy existing positions into a new container, updating the prices if they
  // are available
  std::decay_t<decltype(positions)> refreshed_positions;
  for (auto p : handt::get_positions())
    if (p.open) {

      // If the position is open search for recent prices and update the sell
      // price with the spot
      const auto &q = find_prices(p.symbol);

      if (!q.empty()) {
        p.sell_price = q.back();
        p.status = "refreshd";
      }

      refreshed_positions.emplace_back(p);
    }

  // Calculate total prices processed and store it
  const auto total_prices_processed = prices.size() + handt::get_stats();
  handt::put_stats(total_prices_processed);

  // Report all positions
  for (const auto position : refreshed_positions)
    std::cout << position << '\n';

  std::cout << "# " << prices.size() << " prices this iteration\n";
  std::cout << "# " << total_prices_processed << " total prices processed\n";
  std::cout << "# " << refreshed_positions.size() << " positions\n";
}
