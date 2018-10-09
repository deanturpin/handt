#include "report.h"
#include <numeric>
#include <sstream>
#include <string>

// Take a container of all backtests and produce a report as a string

std::string get_report(const std::vector<trade_t> &prices,
                       const std::vector<backtest_t> &backtests,
                       const unsigned int &max_entries,
                       const bool &prospects_only) {

  std::stringstream out;
  out << "\nStrategy|Pair|Good/Bad|Spot|Last (days)\n"
      << "---|---|---|---|---\n";

  unsigned int entries = 0;
  for (const auto &s : backtests)
    if (!prospects_only || s.buy) {

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

                     : s.exchange == std::string("Poloniex")
                           ? "poloniex.com/exchange#" + s.from_symbol + '_' +
                                 s.to_symbol
                           : "no_url");

      // Report strategy summary
      out << s.name << '|' << "[" << s.from_symbol << '-' << s.to_symbol << "]("
          << url << ")|" << s.good_deals.size() << '/' << s.bad_deals.size()
          << '|' << s.spot << '|'
          << (prices.back().prices.size() - s.good_deals.back().first) / 24
          << '\n';

      ++entries;

      if (entries > max_entries)
        break;
    }

  return out.str();
}
