#include "handt.h"
#include <algorithm>
#include <iterator>
#include <vector>

int main() {

  // Get all review positions
  const auto &reviewed_positions = handt::get_reviewed_positions();

  // Filter closed positions
  std::decay_t<decltype(reviewed_positions)> closed_positions;
  std::copy_if(reviewed_positions.cbegin(), reviewed_positions.cend(),
               std::back_inserter(closed_positions),
               [](const auto &position) { return !position.open; });

  // Read current balance
  const std::string filename("balance.csv");
  std::ifstream file(filename);
  double balance = 1000000.0;
  if (file.good())
    file >> balance;
  file.close();

  const double trade_size = 1000.0;

  // Update balance for each closed position
  for (const auto &position : closed_positions)
    balance += trade_size * position.yield() - trade_size;

  // Write the updateed balance back
  std::ofstream file_out(filename);
  if (file_out.good())
    file_out << balance;
}
