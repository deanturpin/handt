#include "handt.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <iomanip>
#include <string>
#include <vector>

int main() {

  // Configure debug
  std::stringstream out;
  out.precision(2);
  out << std::fixed;

  out << R"(
<!DOCTYPE html>

<meta charset="UTF-8">
<meta name="robots" content="index,follow" />
<meta http-equiv="refresh" content="30" />
<link rel=icon href="favicon.ico" sizes="any">

<style>
body { font-family: sans-serif; }
pre#floater {
  float: right;
  text-align: right;
}
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
each batch and a position is created if the strategy returns positively.
Positions are closed if either the sell price exceeds 106 % of the buy price or
24 hours have elapsed since it was created.

The balance is updated as each positions is closed and all trades are $1000.
This isn't an real balance but does give a feel for how well the strategies are
performing. The $1000 trade was chosen as it's large enough to not worry about
the fees on a Coinbase trade.
</p>

)";

  // Get some data to play with
  const auto &prices = handt::get_prices();
  const auto &symbols = handt::get_symbols();
  const auto &positions = handt::get_final_positions();
  const auto &balance = handt::get_balance();
  const auto open_positions = positions.size();

  // Pretty print
  const auto plural = prices.size() == 1 ? "" : "s";

  // Trade summary
  out << "<h2>Balance: $" << balance
    << " - " << open_positions << " open positions</h2>";
  out << "<p>";
  out << symbols.size() << " tradable symbols listed on CryptoCompare, ";
  out << prices.size() << " coin" << plural << " updated in the last minute.";
  out << "</p>\n";

  // Close all positions and split into cap size
  std::map<std::string, std::vector<double>> strategy_summary, coins;
  for (const auto &position : positions) {

    const auto strategy = position.strategy;
    const auto symbol = position.symbol;
    const auto yield = position.yield();

    strategy_summary[strategy].push_back(yield);
    coins[symbol].push_back(yield);
  }

  out << "<pre id='floater'>\n";
  std::vector<std::pair<std::string, double>> coin_summary;

  // Calculate coin averages and sort
  for (const auto &coin : coins)
    if (!coin.second.empty())
      coin_summary.push_back(std::make_pair(
          coin.first,
          100.0 *
              std::accumulate(coin.second.cbegin(), coin.second.cend(), 0.0) /
              coin.second.size()));

  std::sort(coin_summary.begin(), coin_summary.end(),
            [](const auto &a, const auto &b) { return a.second > b.second; });

  // Print the best performing currencies
  out << "Top symbols\n";
  for (auto i = coin_summary.cbegin();
       i != std::min(coin_summary.cend(), std::next(coin_summary.cbegin(), 30));
       ++i)
    out << i->first << "\t" << i->second << '\n';

  out << "</pre>\n<pre>\n";

  // Print strategy summaries
  out << "STRATEGY\t\t POS\t% RETURN\n";
  for (const auto &i : strategy_summary) {
    const unsigned long positions_held = i.second.size();
    const double yield =
        100.0 * std::accumulate(i.second.cbegin(), i.second.cend(), 0.0) /
        positions_held;

    out << i.first << "\t" << positions_held << "\t" << yield << "\n";
  }

  out << "</pre>\n";

  std::cout << out.str();
}
