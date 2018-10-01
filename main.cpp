#include "backtest.h"
#include "detailed_report.h"
#include "perms.h"
#include "report.h"
#include "trade.h"
#include "unit_test.h"
#include <iostream>

int main() {

  unit_test();

  // Get the latest prices
  const auto &trades = get_trades();

  // Get the strategies
  const auto &strategies = get_strategies();

  // Run backtests
  const auto &backtests = run_backtests(trades, strategies);

  // Generate report for deployment
  const auto &report = get_report(trades, strategies, backtests);

  // Generate detailed report of analysis
  const auto &detailed_report = get_detailed_report(trades, backtests);

  std::cout.imbue(std::locale(""));
  std::cout << "* " << trades.size() << " currency pairs\n"
            << "* " << strategies.size() << " strategies\n"
            << "* " << backtests.size() << " backtests\n\n"
            << report << '\n'
            << detailed_report << '\n';
}
