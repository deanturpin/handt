#include "report.h"
#include <numeric>
#include <string>

// Take a container of all backtests and produce a report as a string

std::string get_report(const std::vector<trade_t> &prices,
                       const std::vector<backtest_t> &backtests) {

  std::stringstream out;

  // Calculate total tests performed during backtesting
  const auto tests_performed = std::accumulate(
      backtests.cbegin(), backtests.cend(), 0ul,
      [](unsigned int sum, const auto &p) { return sum + p.opportunities; });

  // Pretty print large numbers
  out.imbue(std::locale(""));
  out << "* " << prices.size() << " currency pairs\n";
  out << "* " << backtests.size() << " strategy/pair combinations\n";
  out << "* " << tests_performed << " backtests\n\n";

  // Report individual strategy performance
  out << "# Current prospects\n"
      << "Prospects based on prices from the last 24 hours.\n\n"
      << "Strategy|Pair|Good/Bad|Spot|Last (days)\n"
      << "---|---|---|---|---\n";

  unsigned int buy_count = 0;
  for (const auto &s : backtests)
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
          << url << ")|" << s.good_deals.size() << '/' << s.bad_deals.size()
          << '|' << s.spot << '|'
          << (prices.back().prices.size() - s.good_deals.back().first) / 24
          << '\n';

      ++buy_count;

      if (buy_count > 10)
        break;
    }

  // Report individual strategy performance
  out << R"(
# 80-day backtest
The results are ordered by success which is measured using the proportion of
good to bad trades.

Strategy|Pair|Good/Bad|Spot
---|---|---|---
)";

  for (const auto &s : backtests) {

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
        << url << ")|" << s.good_deals.size() << '/' << s.bad_deals.size()
        << '|' << s.spot << '\n';
  }

  return out.str();
}
