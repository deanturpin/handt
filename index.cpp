#include "include/handt.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <regex>

#include <sstream>
#include <string>

#include <vector>

int main() {

  // Get some data to play with
  const auto &consolidated = handt::get_consolidated_positions();
  const auto &closed_positions = handt::get_closed_positions();
  const auto &symbols = handt::get_symbols().size();
  const auto batch_size = 60ul;

  // Get the HTML template
  std::string index = handt::get_index_html();

  // Wrapper functor for in-place regex substitution
  const auto substitute_inline =
    [](std::string &in, const std::string &token,
                                    const std::string &value) {
    const auto out = std::regex_replace(in, std::regex(token), value);
    in = out;
  };

  // Define tokens and what we'd like them to be replaced with
  const
    
    std::map<std::string, std::string> tokens{
      {"STATS", std::to_string(handt::get_stats())},
      {"DATE",
        handt::get_date()},
      {"UNIT_TEST", handt::get_unit_test_results()},
      {"BATCH", std::to_string(batch_size)},
      {"SYMBOLS", std::to_string(symbols)},
      {"GITLOG", handt::get_git_log()},
      {"MINUTES", std::to_string(symbols / batch_size)},
      {"SELL_THRESHOLD", std::to_string(static_cast<unsigned long>(
                             handt::sell_threshold * 100.0))},
      {"CUT", std::to_string(static_cast<unsigned long>(
                  handt::cut_losses_threshold * 100.0))}};

  // Replace all tokens
  for (const auto &t : tokens)
    substitute_inline(index, t.first, t.second);

  // Structure for reporting strategy performance
  struct yield_summary {
    std::string name;
    std::vector<double> returns;

    // Calculate average yield of all the positions created by current strategy
    double average_yield() const {
      return std::accumulate(returns.cbegin(), returns.cend(), 0.0,
                             [](auto &sum, const auto &y) { return sum + y; }) /
             (returns.size() > 0 ? returns.size() : 1);
    }

    auto min_yield() const {
      return *std::min_element(returns.cbegin(), returns.cend());
    }

    auto max_yield() const {
      return *std::max_element(returns.cbegin(), returns.cend());
    }

    std::string report() const {
      std::stringstream ss;
      ss.precision(0);
      ss << std::fixed;
      ss << name << '\t' << returns.size() << '\t' << 100.0 * min_yield()
         << '\t' << 100.0 * average_yield() << '\t' << 100.0 * max_yield();
      return ss.str();
    }
  };

  // Review all closed positions and generate some summaries
  std::vector<yield_summary> all_coins_strategy_summary,
      coinbase_strategy_summary, all_coins_performance;
  for (const auto &position : closed_positions) {

    // Iterate over Coinbase closed positions and create strategy summary
    if (position.symbol == "ETH" || position.symbol == "BTC" ||
        position.symbol == "BCH" || position.symbol == "LTC") {

      const auto strategy = position.strategy;
      const auto it = find_if(
          coinbase_strategy_summary.begin(), coinbase_strategy_summary.end(),
          [&strategy](const auto &p) { return strategy == p.name; });

      // If strategy record doesn't exist, create a new one and insert it,
      // otherwise just update the position count
      if (it == coinbase_strategy_summary.end()) {

        yield_summary strat;
        strat.name = strategy;
        strat.returns.push_back(position.yield());
        coinbase_strategy_summary.emplace_back(strat);

      } else
        it->returns.push_back(position.yield());
    }

    // Iterate over all closed positions and create coins performance summary
    {
      const auto name = position.symbol;
      const auto it =
          find_if(all_coins_performance.begin(), all_coins_performance.end(),
                  [&name](const auto &p) { return name == p.name; });

      // If coin record doesn't exist, create a new one and insert it
      if (it == all_coins_performance.end()) {

        yield_summary coin;
        coin.name = name;
        coin.returns.push_back(position.yield());
        all_coins_performance.emplace_back(coin);

      } else
        it->returns.push_back(position.yield());
    }

    // Iterate over all closed positions and create strategy summary
    {
      const auto name = position.strategy;
      const auto it = find_if(
          all_coins_strategy_summary.begin(), all_coins_strategy_summary.end(),
          [&name](const auto &s) { return name == s.name; });

      // If strategy record doesn't exist, create a new one and insert it,
      // otherwise just update the position count
      if (it == all_coins_strategy_summary.end()) {

        yield_summary strat;
        strat.name = name;
        strat.returns.push_back(position.yield());
        all_coins_strategy_summary.emplace_back(strat);

      } else
        it->returns.push_back(position.yield());
    }
  }

  // Sort all coins strategy summary by number of positions - an indicator of
  // confidence in the return: a high yield with few closed positions suggests a
  // low confidence
  std::sort(all_coins_strategy_summary.begin(),
            all_coins_strategy_summary.end(), [](const auto &a, const auto &b) {
              return a.returns.size() > b.returns.size();
            });

  // Sort Coinbase strategy cummary
  std::sort(coinbase_strategy_summary.begin(), coinbase_strategy_summary.end(),
            [](const auto &a, const auto &b) {
              return a.returns.size() > b.returns.size();
            });

  // Sort coin performance summary
  std::sort(all_coins_performance.begin(), all_coins_performance.end(),
            [](const auto &a, const auto &b) {
              return a.returns.size() > b.returns.size();
            });

  // Extract open Coinbase positions
  std::vector<handt::position> coinbase_open;
  for (const auto &position : consolidated)
    if (position.symbol == "ETH" || position.symbol == "BTC" ||
        position.symbol == "BCH" || position.symbol == "LTC")
      coinbase_open.push_back(position);

  // Sort open positions for display
  std::sort(
      coinbase_open.begin(), coinbase_open.end(),
      [](const auto &a, const auto &b) { return a.timestamp > b.timestamp; });

  // Report open Coinbase positions
  std::stringstream open_pos;
  open_pos.precision(0);
  open_pos << std::fixed;
  for (const auto &position : coinbase_open)
    open_pos << position.symbol << '\t' << position.yield() * 100.0 << '\t'
             << position.strategy << '\t' << position.buy_price << '\t'
             << position.sell_price << '\t'
             << 24.0 - (handt::get_timestamp() - position.timestamp) / 3600.0
             << '\n';

  substitute_inline(index, "COINBASE_OPEN", open_pos.str());

  // Report summary of open and closed positions
  std::stringstream open_and_closed;
  open_and_closed << consolidated.size() << " open positions, "
                  << closed_positions.size() << " closed\n\n";
  substitute_inline(index, "POSITIONS", open_and_closed.str());

  // Report succesful strategy summary for all coins
  std::stringstream allcoins_summary;
  for (const auto &strategy : all_coins_strategy_summary)
    if (strategy.average_yield() > handt::sell_threshold)
      if (strategy.min_yield() > handt::cut_losses_threshold)
        allcoins_summary << strategy.report() << '\n';

  substitute_inline(index, "ALLCOINS_STRATEGY", allcoins_summary.str());

  // Report strategy summary for Coinbase coins
  std::stringstream coinbase_summary;
  for (const auto &strategy : coinbase_strategy_summary)
    if (strategy.average_yield() > handt::sell_threshold)
      if (strategy.min_yield() > handt::cut_losses_threshold)
        coinbase_summary << strategy.report() << '\n';

  substitute_inline(index, "COINBASE_STRATEGY", coinbase_summary.str());

  // Report coin performance
  std::stringstream coin_performance;
  for (const auto &coin : all_coins_performance)
    if (coin.average_yield() > handt::sell_threshold &&
        coin.min_yield() > handt::cut_losses_threshold &&
        coin.min_yield() < handt::cut_losses_threshold * 2.0)
      coin_performance << coin.report() << '\n';

  substitute_inline(index, "COIN_PERFORMANCE", coin_performance.str());

  std::cout << index;
}
