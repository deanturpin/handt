#include "backtest.h"
#include "detailed_report.h"
#include "parallel.h"
#include "report.h"
#include "strategy.h"
#include "strategy_report.h"
#include "trade.h"
#include "unit_test.h"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>

int main() {

  unit_test();

  std::cerr << "Get latest prices for all currency pairs\n";
  const auto &trades = get_trades();

  std::cerr << "Get all strategy permutations\n";
  const auto &strategies = get_strategies();

  std::cerr << "Run backtests\n";
  const auto &backtests = run_backtests(trades, strategies);

  std::cerr << "Generate reports for deployment\n";
  const auto &prospects_report = get_report(trades, backtests, 10, true);
  const auto &backtest_report = get_report(trades, backtests, 300, false);

  std::cerr << "Generate detailed report for offline analysis";
  get_detailed_report(trades, backtests);

  std::cerr << "Generate summary of all strategy performance";
  const auto &strategy_report = get_strategy_report(backtests);

  std::cerr << "Create printable timestamp\n";
  using namespace std::chrono;
  const auto end_time = system_clock::to_time_t(system_clock::now());
  const auto generated_timestamp = std::ctime(&end_time);

  std::cerr << "Calculate total backtests performed\n";
  const auto total_backtests = std::accumulate(
      backtests.cbegin(), backtests.cend(), 0ul,
      [](unsigned int sum, const auto &p) { return sum + p.opportunities; });

  std::cout.imbue(std::locale(""));
  std::cout << "Generated " << generated_timestamp << '\n'
            << "* " << parallel::thread_count << " threads\n"
            << "* " << trades.size() << " currency pairs\n"
            << "* " << strategies.size() << " strategies\n"
            << "* " << total_backtests << " backtests\n\n"
            << "# Current prospects\n"
            << prospects_report << '\n'
            << "# 80-day backtest\n"
            << backtest_report << '\n'
            << "# Strategy performance summary\n"
            << strategy_report << '\n';
}
