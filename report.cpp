#include "report.h"
#include <numeric>
#include <sstream>
#include <string>
#include <string_view>

// Parse backtest results and generate strategy performance report

// Take a container of all backtests and produce a report as a string
static std::string construct_exchange_url(const std::string &from_symbol,
                                          const std::string &to_symbol,
                                          const std::string &exchange) {

  // Trim any trailing asterisk from symbol name
  std::string_view from_symbol_trimmed = from_symbol;
  if (from_symbol_trimmed.back() == '*')
    from_symbol_trimmed.remove_suffix(1);

  if (exchange == std::string("Coinbase"))
    return "https://coinbase.com";

  if (exchange == std::string("Binance"))
    return "https://binance.com/en/trade/" + std::string(from_symbol_trimmed) +
           '_' + to_symbol;

  if (exchange == std::string("Poloniex"))
    return "https://poloniex.com/exchange#" + to_symbol + '_' + from_symbol;

  return "http://lmgtfy.com/?q=" + exchange;
}

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

      // Construct exchange URL
      const auto url =
          construct_exchange_url(s.from_symbol, s.to_symbol, s.exchange);

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
