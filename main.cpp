#include "backtest.h"
#include "detailed_report.h"
#include "perms.h"
#include "report.h"
#include "trade.h"
#include "unit_test.h"

int main() {

  unit_test();

  // Get the latest prices
  const auto &trades = get_trades();

  // Get the strategies
  const auto &perms = get_strategies();

  // Run backtests
  const auto &backtests = run_backtests(trades, perms);

  // Generate report for deployment
  const auto &report = get_report(trades, backtests);

  // Print report
  std::puts(report.c_str());

  // Generate detailed report of analysis
  const auto &detailed_report = get_detailed_report(trades, backtests);
  std::fputs(detailed_report.c_str(), stderr);
}
