#include "handt.h"
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

int main() {

  // Configure debug
  std::stringstream out;
  out.precision(10);
  out << std::boolalpha;
  out << std::fixed;

  out << R"(
<!DOCTYPE html>

<meta charset="UTF-8">
<meta name="robots" content="index,follow" />
<meta http-equiv="refresh" content="30" />
<link rel=icon href="favicon.ico" sizes="any">

<style>
body { font-family: sans-serif; }
</style>

<title>HANDT</title>
<h1>HAVE A NICE DAY TRADER</h1>

<p id="disclaimer">History is no indicator of future performance. Don't invest
what you can't afford to lose. Prices fetched periodically from <a
href="https://www.cryptocompare.com/api/" target="blah">CryptoCompare</a>. See
the documentation on <a href="https://deanturpin.github.io/handt"
target="blah">GitHub</a>.</p>

)";

  out << "<pre>\n";

  // Get the coins
  const auto prices = handt::get_prices();
  out << prices.size() << " coins updated in the last minute\n";

  // Get the positions
  const auto positions = handt::get_positions("consolidate.csv");
  out << positions.size() << " positions\n\n";

  std::map<std::string, std::vector<double>> small_cap, big_cap;

  // Close all positions
  for (const auto &position : positions) {

    if (position.buy_price < 10.0)
      small_cap[position.strategy].push_back(position.sell_price /
                                             position.buy_price);
    else
      big_cap[position.strategy].push_back(position.sell_price /
                                           position.buy_price);
  }

  out << "SMALLCAP\t\t POS\t% RETURN\n";
  for (const auto &i : small_cap) {
    const unsigned long count = i.second.size();
    const double yield =
        100.0 * std::accumulate(i.second.cbegin(), i.second.cend(), 0.0) /
        count;

    out << i.first << "\t" << count << "\t" << yield << "\n";
  }

  out << "\nBIGCAP\t\t\t POS\t% RETURN\n";
  for (const auto &i : big_cap) {
    const unsigned long count = i.second.size();
    const double yield =
        100.0 * std::accumulate(i.second.cbegin(), i.second.cend(), 0.0) /
        count;

    out << i.first << "\t" << count << "\t" << yield << "\n";
  }

  out << "<pre>\n";
  std::cout << out.str();
}
