#include "report.h"
#include <cassert>
#include <fstream>
#include <numeric>
#include <string>

// Take a container of all backtests and produce a report as a string

std::string get_report(const prices_t &prices,
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
          << url << ")|" << s.good_deals.size() << '/' << s.bad_deals.size()
          << '|' << s.spot << '\n';

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
        << url << ")|" << s.good_deals.size() << '/' << s.bad_deals.size()
        << '|' << s.spot << '\n';
  }

  return out.str();
}

// Generate detailed internal report
std::string get_detailed_report(const prices_t &prices,
                                const std::list<backtest_t> &backtests) {

  std::stringstream report;

  int iterations = 0;
  for (const auto &b : backtests) {
    report << b.name << ' ' << b.from_symbol << ' ' << b.to_symbol << " - ";

    for (const auto &[start, end] : b.good_deals) {
      const int diff = end - start;
      assert(diff < 48 && "trade too long");
      report << start << '/' << end << '/' << diff << ' ';
    }

    report << " - " << b.bad_deals.size() << '\n';

    // Look up the prices for this backtest
    const auto it = std::find_if(
        prices.cbegin(), prices.cend(),
        [from_symbol = b.from_symbol, to_symbol = b.to_symbol](const auto p) {
          return p.from_symbol == from_symbol && p.to_symbol == to_symbol;
        });

    if (it != prices.cend()) {
      const std::string file_name = "tmp/" + b.name + ".csv";
      std::ofstream out(file_name);
      for (const auto &p : it->prices)
        out << p << ", \n";
    }

    // In lieu of for_each_n :(
    ++iterations;
    if (iterations > 10)
      break;
  }

  return report.str();
}
