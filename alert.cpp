#include "position.h"
#include "utils.h"
#include <fstream>
#include <iterator>
#include <iostream>
#include <vector>
#include <string>

int main() {

  // The coins we can trade in
  const std::vector<std::string> coins = { "BTC", "ETH", "BCH", "LTC" };

  std::copy(std::begin(coins), std::end(coins), std::ostream_iterator<decltype(coins.front())>(std::cout, " "));
  std::cout << "interesting coins\n";

  // Get the buys
  const std::vector<trade_position> buys(get_positions("buys.csv"));
  std::cout << buys.size() << " positions held\n";

  // Get the sells
  const std::vector<trade_position> sells(get_positions("sells.csv"));
  std::cout << sells.size() << " complete transactions\n\n";
}
