#include "handt.h"
#include <algorithm>
#include <vector>

int main() {

  // Read current balance and trade size
  double balance = handt::get_balance();
  const double &trade_size = handt::trade_size;

  // Update balance for each closed position
  for (const auto &position : handt::get_reviewed_positions())
    if (!position.open)
      balance += (trade_size * position.yield()) - trade_size;

  // Write the updated balance back
  handt::put_balance(balance);
}
