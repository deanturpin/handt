#include "handt.h"
#include <algorithm>
#include <string>
#include <vector>

int main() {

  // Get the final set of positions after trading is complete
  const auto &positions = handt::get_final_positions();

  // Define some interesting symbols
  const std::vector<std::string> symbols {"BTC", "LTC", "ETH", "BCH"};

  const auto it = std::find_first_of(positions.cbegin(), positions.cend(),
                                     symbols.cbegin(), symbols.cend(),
                                     [](const auto &coin, const auto &symbol) {
                                       return coin.symbol == symbol;

                                     });

  // Return positively if we found a symbol
  return (it != positions.cend() ? 0 : 1);
}
