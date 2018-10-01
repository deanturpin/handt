#include "detailed_report.h"
#include <fstream>
#include <sstream>
#include <string>

// Generate detailed internal report
std::string get_detailed_report(const prices_t &prices,
                                const std::vector<backtest_t> &backtests) {

  std::stringstream report;

  int iterations = 0;
  for (const auto &b : backtests) {
    report << b.name << ' ' << b.from_symbol << ' ' << b.to_symbol << " - ";

    for (const auto &[start, end] : b.good_deals)
      report << start << '/' << end << '/' << end - start << ' ';

    report << " - " << b.good_deals.size() << '/' << b.bad_deals.size() << '\n';

    // Look up the prices for this backtest
    const auto it = std::find_if(
        prices.cbegin(), prices.cend(),
        [from_symbol = b.from_symbol, to_symbol = b.to_symbol](const auto p) {
          return p.from_symbol == from_symbol && p.to_symbol == to_symbol;
        });

    if (it != prices.cend()) {
      const std::string file_name = "analysis/" + b.name + '-' + b.from_symbol +
                                    '-' + b.to_symbol + ".csv";

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
