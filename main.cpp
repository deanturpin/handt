#include "backtest.h"
#include "perms.h"
#include "prices.h"
#include "report.h"
#include "unit_test.h"
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
    std::cout << b.name << " - " << b.good_deals << '\n';
    ++iterations;
    if (iterations > 10)
      break;
  }
}
