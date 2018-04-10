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

    // Calculate average yield of all the positions created by current strategy
    double average_yield() const {
        return std::accumulate(returns.cbegin(), returns.cend(), 0.0,
                        [](auto &sum, const auto &y) { return sum + y; }) /
        (returns.size() > 0 ? returns.size() : 1);
      }

    // Return list of symbols that matured under current strategy
    std::string symbol_list() const {

      std::stringstream symbol_string;
      for (const auto &symbol : symbols)
        symbol_string << symbol.first << ' ';

      return symbol_string.str();
    }
  };

  // Iterate over all closed positions and create strategy summary
  std::vector<strategy_summary> all_coins;
  for (const auto &position : closed) {
    const auto strategy = position.strategy;
    const auto it =
        find_if(all_coins.begin(), all_coins.end(),
                [&strategy](const auto &s) { return strategy == s.name; });

    // If strategy record doesn't exist, create a new one and insert it
    if (it == all_coins.end()) {
      strategy_summary strat;
      strat.name = strategy;
      strat.returns.push_back(position.yield());

      // Only store symbol if it's matured
      if (position.yield() > .90) // handt::sell_threshold)
        strat.symbols[position.symbol] = 1;

      all_coins.emplace_back(strat);
    }
    else {
      // Otherwise just update the position count
      it->returns.push_back(position.yield());

      // Only store symbol if it's matured
      if (position.yield() > handt::sell_threshold)
          ++it->symbols[position.symbol];
    }
  }

  // Iterate over Coinbase closed positions and create strategy summary
  std::vector<strategy_summary> coinbase;
  for (const auto &position : closed) {
    const auto strategy = position.strategy;
    const auto it =
        find_if(coinbase.begin(), coinbase.end(),
                [&strategy](const auto &s) { return strategy == s.name; });

    // If strategy record doesn't exist, create a new one and insert it
    if (it == coinbase.end()) {
      strategy_summary strat;
      strat.name = strategy;
      strat.returns.push_back(position.yield());

      // Only store symbol if it's matured
      if (position.yield() > .90) // handt::sell_threshold)
        strat.symbols[position.symbol] = 1;

      if (position.symbol == "ETH" || position.symbol == "BTC" ||
          position.symbol == "BCH" || position.symbol == "LTC")
        coinbase.emplace_back(strat);
    }
    else {
      // Otherwise just update the position count
      it->returns.push_back(position.yield());

      // Only store symbol if it's matured
      if (position.yield() > handt::sell_threshold)
          ++it->symbols[position.symbol];
    }
  }

  // Sort strategy summaries by number of positions - an indicator of confidence
  // in the return: a high yield with few closed positions suggests a low
  // confidence
  std::sort(all_coins.begin(), all_coins.end(), [](const auto &a, const auto &b) {
    return a.returns.size() > b.returns.size();
  });
  std::sort(coinbase.begin(), coinbase.end(), [](const auto &a, const auto &b) {
    return a.returns.size() > b.returns.size();
  });

  // Print strategy summary for all coins
  out << "<h1>All coins strategy summary</h1>\n";
  out << "<pre>\n";
  out << "STRATEGY\t\t POS\t% RETURN\tMATURED SYMBOLS\n";
  for (const auto &strategy : all_coins)
    out << strategy.name << '\t' << strategy.returns.size() << '\t'
      << 100.0 * strategy.average_yield() << "\t\t"
        << strategy.symbol_list() << '\n';
  out << "</pre>\n";

  // Print strategy summary for Coinbase coins
  out << "<h1>Coinbase strategy summary</h1>\n";
  out << "<pre>\n";
  for (const auto &strategy : coinbase)
    out << strategy.name << '\t' << strategy.returns.size() << '\t'
    << 100.0 * strategy.average_yield() << "\t\t"
    << strategy.symbol_list() << '\n';

  out << "</pre>\n";

  std::cout << out.str();
}
