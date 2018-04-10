#include "handt.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

int main() {

  // Configure debug
  std::stringstream out;
  out.precision(2);
  out << std::fixed;

  // Get some data to play with
  const auto &closed = handt::get_closed_positions();
  const auto &symbols = handt::get_symbols().size();
  const unsigned long batch_size = 80UL;

  // Print the bulk of the HTML
  out << R"(
<!DOCTYPE html>

<meta charset="UTF-8">
<meta name="robots" content="index,follow" />
<meta http-equiv="refresh" content="30" />
<link rel=icon href="favicon.ico" sizes="any">

<style>
body {
  font-family: sans-serif;
  background-color: #234;
  color: white;
}
a:link, a:visited { color: lightblue; }
pre#floater { float: right; }
h1 {
  font-size: 100%;
  text-transform: uppercase;
  color: darkorange;
}
</style>

<title>Have A Nice Day Trader</title>
<h1>Have A Nice Day Trader</h1>
<p id="disclaimer">History is no indicator of future performance. Don't invest
what you can't afford to lose. Prices fetched periodically from <a
href="https://www.cryptocompare.com/api/" target="blah">CryptoCompare</a>. See
the documentation on <a href="https://deanturpin.github.io/handt"
target="blah">GitHub</a>.</p>)"
      << "\n\n<p>24 hours of prices are fetched for " << symbols
      << " coins at a rate of " << batch_size
      << " per minute&mdash;a limit set by the exchange&mdash;therefore it "
         "takes "
      << symbols / batch_size
      << " minutes to process the full set of coins. A library of strategies "
         "is run over each batch and a position is created if the strategy "
         "returns positively. Positions are closed if either the sell price "
         "exceeds "
      << handt::sell_threshold * 100.0
      << "&nbsp;% of the buy price or 24 hours have elapsed since creation. A "
         "position can also be closed if the return falls below "
      << handt::cut_losses_threshold * 100.0 << "&nbsp;%. A trade size of $"
      << handt::trade_size << " was chosen as it's large enough to ignore the "
                              "fees on a Coinbase trade.</p>\n\n";

  // Structure for reporting strategy performance
  struct strategy_summary {
    std::string name;
    double yield;
    std::vector<double> returns;
    std::map<std::string, unsigned long> symbols;
  };

  // Iterate over all closed positions and create strategy summary
  std::vector<strategy_summary> summary;
  for (const auto &position : closed) {
    const auto strategy = position.strategy;
    const auto it =
        find_if(summary.begin(), summary.end(),
                [&strategy](const auto &s) { return strategy == s.name; });

    // If strategy record doesn't exist, create a new one and insert it
    if (it == summary.end()) {
      strategy_summary strat;
      strat.name = strategy;
      strat.returns.push_back(position.yield());
      summary.emplace_back(strat);

      // Only store symbol if it's matured
      if (position.yield() > handt::sell_threshold)
        strat.symbols[position.symbol] = 1;
    }
    else {
      // Otherwise just update the position count
      it->returns.push_back(position.yield());

      // Only store symbol if it's matured
      if (position.yield() > handt::sell_threshold)
          ++it->symbols[position.symbol];
    }
  }

  // Sort strategy summaries by number of positions, and indicator of confidence
  // in the return: a high yield with few closed positions suggests a low
  // confidence
  std::sort(summary.begin(), summary.end(), [](const auto &a, const auto &b) {
    return a.returns.size() > b.returns.size();
  });

  // Print strategy summary
  out << "<h1>Strategy summary</h1>\n";
  out << "<pre>\n";
  out << "STRATEGY\t\t POS\t% RETURN\tMATURED SYMBOLS\n";
  for (const auto &strategy : summary) {

    const auto returns = strategy.returns.size();
    const auto yield =
        100.0 *
        std::accumulate(strategy.returns.cbegin(), strategy.returns.cend(), 0.0,
                        [](auto &sum, const auto &y) { return sum + y; }) /
        (returns > 0 ? returns : 1);

    std::stringstream symbols;
    for (const auto &symbol : strategy.symbols)
      symbols << symbol.first << ' ';

    out << strategy.name << '\t' << returns << '\t' << yield << "\t\t"
        << symbols.str() << '\n';
  }
  out << "</pre>\n";

  std::cout << out.str();
}
