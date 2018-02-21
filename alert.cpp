#include "position.h"
#include "utils.h"
#include <fstream>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include <string>

int main() {

  // The coins we can trade in
  const std::vector<std::string> coins = { "BTC", "ETH", "BCH", "LTC" };

  // Get the buys and sells
  const std::vector<trade_position> buys(get_positions("buys.csv"));
  const std::vector<trade_position> sells(get_positions("sells.csv"));

  std::for_each(coins.cbegin(), coins.cend(), [&buys, &sells](const auto &name) {

               if (std::find_if(buys.begin(), buys.end(),
                                 [&name](const auto &coin){
                                 return coin.name == name;
                                 }) != buys.cend())
                 std::cout << name << " prepare to buy\n";

               if (std::find_if(sells.begin(), sells.end(),
                                 [&name](const auto &coin){
                                 return coin.name == name;
                                 }) != sells.cend())
                 std::cout << name << " prepare to sell\n";

                 });
}
