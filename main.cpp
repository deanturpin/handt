#include "backtest.h"
#include "detailed_report.h"
#include "perms.h"
#include "report.h"
#include "trade.h"
#include "unit_test.h"
#include <chrono>
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
  // const auto &prospects_report = get_report(trades, backtests, 10, true);
  // const auto &backtest_report = get_report(trades, backtests, 20, false);

  // // Generate detailed report of analysis
  // const auto &detailed_report = get_detailed_report(trades, backtests);

  // Create printable timestamp
  // const std::time_t end_time =
  //     std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  // const auto generated_timestamp = std::ctime(&end_time);

  // // Calculate total backtest performed
  // const auto total_backtests = std::accumulate(
  //     backtests.cbegin(), backtests.cend(), 0ul,
  //     [](unsigned int sum, const auto &p) { return sum + p.opportunities; });

  // std::cout.imbue(std::locale(""));
  // std::cout << "Generated " << generated_timestamp << '\n'
  //           << "* " << trades.size() << " currency pairs\n"
  //           << "* " << strategies.size() << " strategies\n"
  //           << "* " << total_backtests << " backtests\n\n"
  //           << "# Current prospects\n"
  //           << prospects_report << '\n'
  //           << "# 80-day backtest\n"
  //           << backtest_report << '\n';
}
