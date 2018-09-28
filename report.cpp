#include "report.h"
#include <numeric>
#include <string>

std::string
report_performance(const std::list<strategy_performance> &performance) {

  std::stringstream out;

  // Calculate total tests performed during backtesting
  const auto tests_performed = std::accumulate(
      performance.cbegin(), performance.cend(), 0ul,
      [](unsigned int sum, const auto &p) { return sum + p.opportunities; });

  // Pretty print large numbers
  out.imbue(std::locale(""));

  // Strategy and trade overview
  // std::cout << "* " << currency_pairs.size() << " currency pairs\n"
  //           << "* " << permutations.size() << " strategies\n"
  //           << "* " << performance.size() << " strategy/pair combinations\n"
  //           << "* " << tests_performed << " backtests\n\n";
  out << "* " << performance.size() << " strategy/pair combinations\n";
  out << "* " << tests_performed << " backtests\n\n";

  // Report individual strategy performance
  // std::cout << "# Current prospects (" << sell_threshold
  //           << " % return)\n"
  //              "Prospects based on prices from the last 24 hours.\n\n"
  //              "Strategy|Pair|Good/Bad|Spot\n"
  //              "---|---|---|---\n";

  unsigned int buy_count = 0;
  for (const auto &s : performance)
    if (s.buy) {
      // Trim any trailing asterisk from symbol name
      std::string_view from_symbol_trimmed = s.from_symbol;
      if (from_symbol_trimmed.back() == '*')
        from_symbol_trimmed.remove_suffix(1);

      // Construct exchange URL
      const std::string url =
          "https://" +
          (s.exchange == std::string("Coinbase")
               ? "coinbase.com"
               : s.exchange == std::string("Binance")
                     ? "binance.com/en/trade/" +
                           std::string(from_symbol_trimmed) + '_' + s.to_symbol
                     : "no_url");

      // Report strategy summary
      out << s.name << '|' << "[" << s.from_symbol << '-' << s.to_symbol << "]("
          << url << ")|" << s.good_deals << '/' << s.bad_deals << '|' << s.spot
          << '\n';

      ++buy_count;

      if (buy_count > 10)
        break;
    }

  // Report individual strategy performance
  out << R"(
# Top performers
The results are ordered by success which is measured using the proportion of
good to bad trades.

Strategy|Pair|Good/Bad|Spot
---|---|---|---
)";

  for (const auto &s : performance) {

    // Trim any trailing asterisk from symbol name
    std::string_view from_symbol_trimmed = s.from_symbol;
    if (from_symbol_trimmed.back() == '*')
      from_symbol_trimmed.remove_suffix(1);

    // Construct exchange URL
    const std::string url =
        "https://" +
        (s.exchange == std::string("Coinbase")
             ? "coinbase.com"
             : s.exchange == std::string("Binance")
                   ? "binance.com/en/trade/" +
                         std::string(from_symbol_trimmed) + '_' + s.to_symbol
                   : "no_url");

    // Report strategy summary
    out << s.name << '|' << "[" << s.from_symbol << '-' << s.to_symbol << "]("
        << url << ")|" << s.good_deals << '/' << s.bad_deals << '|' << s.spot
        << '\n';
  }

  return out.str();
}
