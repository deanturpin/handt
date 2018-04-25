#include "handt.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <regex>
#include <string>
#include <vector>

int main() {

  // Configure debug
  std::stringstream out;
  out.precision(2);
  out << std::fixed;

  // Get some data to play with
  const auto &open = handt::get_final_positions();
  const auto &closed = handt::get_closed_positions();
  const auto &symbols = handt::get_symbols().size();
  const unsigned long batch_size = 80UL;

  // Get the HTML template
  std::string index = handt::get_index_html();

  // Wrapper functor for in-place regex substitution
  const auto subst = [](std::string &in, const std::string &token,
                        const std::string &value) {
    const auto out = std::regex_replace(in, std::regex(token), value);
    in = out;
  };

  // Define tokens and what we'd like them to be replaced with
  const std::map<std::string, std::string> tokens{
      {"STATS", std::to_string(handt::get_stats())},
      {"DATE", handt::get_date()},
      {"UNITTEST", handt::get_unittest()},
      {"BATCH", std::to_string(batch_size)},
      {"SYMBOLS", std::to_string(symbols)},
      {"GITLOG", handt::get_git_log()},
      {"MINUTES", std::to_string(symbols / batch_size)},
      {"SELL", std::to_string(
                   static_cast<unsigned long>(handt::sell_threshold * 100.0))},
      {"CUT", std::to_string(static_cast<unsigned long>(
                  handt::cut_losses_threshold * 100.0))}};

  // Replace all tokens
  for (const auto &t : tokens)
    subst(index, t.first, t.second);

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
    } else {
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

    // We're only interested in currency you can buy on Coinbase
    if (position.symbol == "ETH" || position.symbol == "BTC" ||
        position.symbol == "BCH" || position.symbol == "LTC") {

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
        if (position.yield() > handt::sell_threshold)
          strat.symbols[position.symbol] = 1;

        coinbase.emplace_back(strat);
      } else {
        // Otherwise just update the position count
        it->returns.push_back(position.yield());

        // Only store symbol if it's matured
        if (position.yield() > handt::sell_threshold)
          ++it->symbols[position.symbol];
      }
    }
  }

  // Sort strategy summaries by number of positions - an indicator of confidence
  // in the return: a high yield with few closed positions suggests a low
  // confidence
  std::sort(all_coins.begin(), all_coins.end(),
            [](const auto &a, const auto &b) {
              return a.returns.size() > b.returns.size();
            });

  std::sort(coinbase.begin(), coinbase.end(), [](const auto &a, const auto &b) {
    return a.returns.size() > b.returns.size();
  });

  // Extract open Coinbase positions
  std::vector<handt::position> coinbase_open;
  for (const auto &position : open)
    if (position.symbol == "ETH" || position.symbol == "BTC" ||
        position.symbol == "BCH" || position.symbol == "LTC")
      coinbase_open.push_back(position);

  // Sort open positions for display
  std::sort(
      coinbase_open.begin(), coinbase_open.end(),
      [](const auto &a, const auto &b) { return a.timestamp > b.timestamp; });

  // Print open Coinbase positions
  std::stringstream open_pos;
  for (const auto &position : coinbase_open)
    open_pos << position.symbol << '\t' << position.yield() * 100.0 << '\t'
        << position.strategy << '\t' << position.buy_price << '\t'
        << 24.0 - (handt::get_timestamp() - position.timestamp) / 3600.0
        << '\n';

  subst(index, "COINBASE_OPEN", open_pos.str());

  std::stringstream open_and_closed;
  open_and_closed << open.size() << " open positions, " << closed.size()
      << " closed\n\n";
  subst(index, "POSITIONS", open_and_closed.str());

  // Print succesful strategy summary for all coins
  std::stringstream allcoins_summary;
  for (const auto &strategy : all_coins)
    if (strategy.average_yield() > handt::sell_threshold)
      allcoins_summary << strategy.name << '\t' << strategy.returns.size() << '\t'
          << 100.0 * strategy.average_yield() << "\t\t"
          << strategy.symbol_list() << '\n';

  subst(index, "ALLCOINS_STRATEGY", allcoins_summary.str());

  // Print strategy summary for Coinbase coins
  std::stringstream coinbase_summary;
  coinbase_summary.precision(2);
  coinbase_summary << std::fixed;
  for (const auto &strategy : coinbase)
    if (strategy.average_yield() > handt::sell_threshold)
      coinbase_summary << strategy.name << '\t' << strategy.returns.size() << '\t'
          << 100.0 * strategy.average_yield() << "\t\t"
          << strategy.symbol_list() << '\n';

  subst(index, "COINBASE_STRATEGY", coinbase_summary.str());

  // Print populated template
  out << index;

  std::cout << out.str();
}
