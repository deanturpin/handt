#include "handt.h"
#include <algorithm>
#include <vector>

int main() {

  // Get all review positions
  const auto &reviewed_positions = handt::get_reviewed_positions();

  // Read current balance
  double balance = handt::get_balance();

  // Default fixed trade size
  const double trade_size = 1000.0;

  // Update balance for each closed position
  for (const auto &position : reviewed_positions)
    if (!position.open)
      balance += (trade_size * position.yield()) - trade_size;

  // Write the updated balance back
  handt::put_balance(balance);
}
