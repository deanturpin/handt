#include "report.h"
#include <memory>
#include <numeric>
#include <sstream>
#include <string>
#include <string_view>

// Parse backtest results and generate strategy performance report

double mean_variance(const std::vector<double> &prices) {

  // Calculate the diffs
  auto d = std::make_unique<std::vector<double>>(prices.size());
  std::adjacent_difference(prices.begin(), prices.end(), d->data());

  // Pop the large first value off the front
  d->front() = d->back();
  d->pop_back();

  const auto average =
      std::accumulate(prices.cbegin(), prices.cend(), 0.0) / prices.size();

  // Absolute diffs
  std::for_each(d->begin(), d->end(),
                [](auto &element) { element = std::fabs(element); });

  return d->size() > 0
             ? 100.0 *
                   (std::accumulate(d->cbegin(), d->cend(), 0.0) / d->size()) /
                   average
             : 0.0;
}

std::string construct_exchange_url(const std::string &from_symbol) {

  // Trim any trailing asterisk from symbol name
  std::string_view from_symbol_trimmed = from_symbol;
  if (from_symbol_trimmed.back() == '*')
    from_symbol_trimmed.remove_suffix(1);

  return "https://www.cryptocompare.com/coins/" +
         std::string(from_symbol_trimmed);
}

// Take a container of all backtests and produce a report as a string
std::string get_report(const std::vector<trade_t> &prices,
                       const std::vector<backtest_t> &backtests,
                       const unsigned int &max_entries,
                       const bool &prospects_only) {

  std::stringstream out;
  out << "\nStrategy|Pair|Exchange|Perf|Spot|Jitter %\n"
      << "---|---|---|---|---\n";

  unsigned int entries = 0;
  for (const auto &s : backtests)
    if (!prospects_only || s.buy) {

      // Construct exchange URL
      const auto url = construct_exchange_url(s.from_symbol);

      // Find the original prices for this backtest
      const auto it =
          std::find_if(prices.cbegin(), prices.cend(),
                       [exchange = s.exchange, from_symbol = s.from_symbol,
                        to_symbol = s.to_symbol](const auto &p) {
                         return p.exchange == exchange &&
                                p.from_symbol == from_symbol &&
                                p.to_symbol == to_symbol;
                       });

      // Calculate some general stats about the current currency
      const double mv = it == prices.cend() ? 0.0 : mean_variance(it->prices);
      const double spot = it == prices.cend() ? 0.0 : it->prices.back();

      // Report strategy summary
      out << s.name << '|' << "[" << s.from_symbol << '-' << s.to_symbol << "]("
          << url << ")|" << s.exchange << '|' << s.good_deals.size() << '/'
          << s.bad_deals.size() << '|' << spot << '|' << mv << '\n';

      ++entries;

      if (entries > max_entries)
        break;
    }

  return out.str();
}
