#include "backtest.h"
#include "perms.h"
#include "prices.h"
#include "report.h"
#include "unit_test.h"
#include <fstream>
#include <iostream>

int main() {

  unit_test();

  // Get the latest prices
  const auto &prices = get_prices();

  // Get the strategies
  const auto &perms = get_strategies();

  // Run backtests
  const auto &backtests = run_backtests(prices, perms);

  // Generate report for deployment
  // const auto &report = get_report(prices, backtests);
  // std::puts(report.c_str());

  // Generate detailed internal report
  int iterations = 0;
  for (const auto &b : backtests) {
    std::cout << b.name << ' ' << b.from_symbol << ' ' << b.to_symbol << " - ";

    for (const auto &[start, end] : b.good_deals) {
      const int diff = end - start;
      assert(diff < 48 && "trade too long");
      std::cout << start << '/' << end << '/' << diff << ' ';
    }

    std::cout << " - " << b.bad_deals.size() << '\n';

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
}
