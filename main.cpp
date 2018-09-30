#include "backtest.h"
#include "perms.h"
#include "prices.h"
#include "report.h"
#include "unit_test.h"

int main() {

  unit_test();

  // Get the latest prices
  const auto &prices = get_prices();

  // Get the strategies
  const auto &perms = get_strategies();

  // Run backtests
  const auto &backtests = run_backtests(prices, perms);

  // Generate report for deployment
  const auto &report = get_report(prices, backtests);

  // Print report
  std::puts(report.c_str());

  // Generate detailed report of analysis
  const auto &detailed_report = get_detailed_report(prices, backtests);
  std::fputs(detailed_report.c_str(), stderr);
}
