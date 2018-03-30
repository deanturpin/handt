#include "handt.h"
#include <algorithm>
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

<p>24 hours of prices are fetched for approximately 2000 coins at a rate of 80
per minute&mdash;a limit set by the exchange&mdash;therefore it takes around 25
minutes to process the full set of coins. A library of strategies is run over
each batch of 80 and a position is created if the strategy returns positively. A
simple sell strategy is employed: the position is closed if the sell price
exceeds a fixed percentage of the buy price. The first block of results (below)
summarises strategy performance for coins worth less than 10 USD, the second
block is the remaining larger value currencies.</p>

)";

  // Get recent prices
  const auto &prices = handt::get_prices();
  out << "<p>" << prices.size() << " coins updated in the last minute, ";

  // Get the final set of positions after trading is complete
  const auto &positions = handt::get_final_positions();
  out << positions.size() << " consolidated positions.</p>\n";
  out << "<pre>\n";

  // Close all positions and split into cap size
  std::map<std::string, std::vector<double>> small_cap, big_cap, coins;
  for (const auto &position : positions) {

    const auto strategy = position.strategy;
    const auto symbol = position.symbol;
    const auto buy = position.buy_price;
    const auto sell = position.sell_price;
    const auto yield = buy > 0.0 ? sell / buy : 0.0;

    coins[symbol].push_back(yield);

    // Check if it's actually kind of a big deal
    if (buy < 10.0)
      small_cap[strategy].push_back(yield);
    else
      big_cap[strategy].push_back(yield);
  }

  // Print strategy summaries
  out << "STRATEGY\t\t POS\t% RETURN\n";
  for (const auto &strategy : {small_cap, big_cap}) {
    for (const auto &i : strategy) {
      const unsigned long positions_held = i.second.size();
      const double yield =
          100.0 * std::accumulate(i.second.cbegin(), i.second.cend(), 0.0) /
          positions_held;

      out << i.first << "\t" << positions_held << "\t" << yield << "\n";
    }

    out << "--\n";
  }

  std::vector<std::pair<std::string, double>> coin_summary;

  // Calculate coin averages and sort
  for (const auto &coin : coins)
    coin_summary.push_back(std::make_pair(
        coin.first,
        100.0 * std::accumulate(coin.second.cbegin(), coin.second.cend(), 0.0) /
            coin.second.size()));

  std::sort(coin_summary.begin(), coin_summary.end(),
            [](const auto &a, const auto &b) { return a.second > b.second; });

  // Print the best currencies
  out << "Top performing currencies (% RETURN)\n";
  for (auto i = coin_summary.cbegin();
       i != std::next(coin_summary.cbegin(), 20); ++i)
    out << i->first << "\t" << i->second << '\n';

  out << "</pre>\n<hr>\n";
  std::cout << out.str();
}
