#include "detailed_report.h"
#include <fstream>
#include <string>

// Generate detailed internal reports to verify recommended trades

void get_detailed_report(const std::vector<trade_t> &prices,
                         const std::vector<backtest_t> &backtests) {

  int iterations = 0;
  for (const auto &b : backtests) {

    // Look up the prices for this backtest
    const auto it = std::find_if(
        std::cbegin(prices), std::cend(prices),
        [from_symbol = b.from_symbol, to_symbol = b.to_symbol](const auto p) {
          return p.from_symbol == from_symbol && p.to_symbol == to_symbol;
        });

    if (it != std::cend(prices)) {
      const std::string file_name = "analysis/" + b.name + '-' + b.from_symbol +
                                    '-' + b.to_symbol + ".csv";

      std::ofstream out{file_name};
      for (const auto &p : it->prices)
        out << p << ", \n";
    }

    // In lieu of for_each_n :(
    if (++iterations > 10)
      break;
  }
}
