#include "report.h"
#include <numeric>
#include <string>

// Take a container of all backtests and produce a report as a string

std::string report_performance(const prices_t &prices,
                               const std::list<backtest_t> &performance) {

  std::stringstream out;

  // Calculate total tests performed during backtesting
  const auto tests_performed = std::accumulate(
      performance.cbegin(), performance.cend(), 0ul,
      [](unsigned int sum, const auto &p) { return sum + p.opportunities; });

  // Pretty print large numbers
  out.imbue(std::locale(""));
  out << "* " << prices.size() << " currency pairs\n";
  out << "* " << performance.size() << " strategy/pair combinations\n";
  out << "* " << tests_performed << " backtests\n\n";

  // Report individual strategy performance
  out << "# Current prospects\n\n";

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
# 80-day backtest
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
