#include "handt.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

// A prospect has a name, an initial price and a list of strategies that
// triggered the prospect
struct prospect {
  std::string symbol;
  double spot;
  std::vector<std::string> strategies;

  friend std::istream &operator>>(std::istream &is, prospect &p) {
    is >> p.symbol >> p.spot;
    std::copy(std::istream_iterator<std::string>(is),
              std::istream_iterator<std::string>(),
              std::back_inserter(p.strategies));
    return is;
  }
};

int main() {

  // Configure debug
  std::stringstream out;
  out.precision(10);
  out << "# consolidate\n";
  out << std::boolalpha;

  std::vector<prospect> prospects;

  // Read recent prospects
  std::stringstream in = handt::strip_comments("prospects.csv");
  std::string line;
  while (getline(in, line)) {
    std::stringstream ss(line);
    prospect p;
    ss >> p;
    prospects.push_back(p);
  }

  // Get existing reviewed positions
  const auto existing_positions = handt::get_positions("review.csv");

  // Create new postion for each propsect
  std::decay_t<decltype(existing_positions)> new_positions;
  for (const auto &prospect : prospects) {
    for (const auto &strategy : prospect.strategies) {

      // Check if we already hold an open position with this currency/strategy
      const auto symbol = prospect.symbol;
      const auto it = std::find_if(
          existing_positions.cbegin(), existing_positions.cend(),
          [&symbol, &strategy](const auto p) {
            return p.open && p.symbol == symbol && p.strategy == strategy;
          });

      // Create a position if we don't already hold one
      if (it == existing_positions.cend()) {

        // Initialise position with prospect details and store it
        handt::position position;
        position.symbol = prospect.symbol;
        position.strategy = strategy;
        position.buy_price = position.sell_price = prospect.spot;
        new_positions.push_back(position);
      }
    }
  }

  out << "# " << existing_positions.size() << " existing positions\n";
  for (const auto &p : existing_positions)
    out << p << "\n";

  out << "# " << new_positions.size() << " new positions\n";
  for (const auto &p : new_positions)
    out << p << "\n";

  std::cout << out.str();
}
