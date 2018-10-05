#include "backtest.h"
#include "detailed_report.h"
#include "parallel.h"
#include "perms.h"
#include "report.h"
#include "trade.h"
#include "unit_test.h"
#include <chrono>
#include <iostream>

#include <map>
#include <sstream>

std::string get_strategy_report(const std::vector<backtest_t> &backtests) {

  std::stringstream report;

  struct perf {
    unsigned int good = 0;
    unsigned int bad = 0;
  };

  // std::vector<std::pair<
  // 	std::string, std::vector<perf>
  // 	>
  // 	> strategy_performance;

  std::map<std::string, perf> strategy_performance;

  for (const auto &b : backtests) {
    strategy_performance[b.name].good += b.good_deals.size();
    strategy_performance[b.name].bad += b.bad_deals.size();
  }

  for (const auto &[name, performance] : strategy_performance)
    report << name << ' ' << performance.good << ' ' << performance.bad << '\n';

  return report.str();
}

int main() {

  unit_test();

  // Get latest prices for all currency pairs
  const auto &trades = get_trades();

  // Get all strategy permutations
  const auto &strategies = get_strategies();

  // Run backtests
  const auto &backtests = run_backtests(trades, strategies);

  // Generate reports for deployment
  const auto &backtest_report = get_report(trades, backtests, 20, false);
  const auto &prospects_report = get_report(trades, backtests, 10, true);

  // Generate detailed report for offline analysis
  get_detailed_report(trades, backtests);

  // Generate summary of all strategy performance
  const auto &strategy_report = get_strategy_report(backtests);

  // Create printable timestamp
  using namespace std::chrono;
  const auto end_time = system_clock::to_time_t(system_clock::now());
  const auto generated_timestamp = std::ctime(&end_time);

  // Calculate total backtests performed
  const auto total_backtests = std::accumulate(
      backtests.cbegin(), backtests.cend(), 0ul,
      [](unsigned int sum, const auto &p) { return sum + p.opportunities; });

  std::cout.imbue(std::locale(""));
  std::cout << "Generated " << generated_timestamp << '\n'
            << "* " << parallel::thread_count << " threads\n"
            << "* " << trades.size() << " currency pairs\n"
            << "* " << strategies.size() << " strategies\n"
            << "* " << total_backtests << " backtests\n\n"
            << "# Strategy performance\n"
            << strategy_report << '\n'
            << "# Current prospects\n"
            << prospects_report << '\n'
            << "# 80-day backtest\n"
            << backtest_report << '\n';
}
