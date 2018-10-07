#include "strategy_report.h"
#include <algorithm>
#include <sstream>

std::string get_strategy_report(const std::vector<backtest_t> &backtests) {

  std::stringstream report;

  struct perf {
    unsigned int good = 0;
    unsigned int bad = 0;
  };

  std::vector<std::pair<std::string, perf>> strategy_performance;

  for (const auto &b : backtests) {

    // See if we have already have an entry for the current strategy
    auto it = std::find_if(
        strategy_performance.begin(), strategy_performance.end(),
        [&name = b.name](const auto &s) { return s.first == name; });

    if (it == strategy_performance.end()) {
      strategy_performance.push_back({b.name, {}});
      it = std::prev(strategy_performance.end());
    }

    it->second.good += b.good_deals.size();
    it->second.bad += b.bad_deals.size();
  }

  // Sort backtests by success
  std::stable_sort(
      strategy_performance.begin(), strategy_performance.end(),
      [](const auto &a, const auto &b) {
        const unsigned int agd = a.second.good;
        const unsigned int bgd = b.second.good;
        const unsigned int abd = a.second.bad;
        const unsigned int bbd = b.second.bad;

        return static_cast<double>(agd ? agd : .9) / (abd ? abd : .9) >
               static_cast<double>(bgd ? bgd : .9) / (bbd ? bbd : .9);
      });

  report << strategy_performance.size() << " strategies\n";

  report << "```\n";
  unsigned int entries = 0;
  for (const auto &[name, performance] : strategy_performance) {
    report << name << ' ' << performance.good << '/' << performance.bad << '\n';

    ++entries;
    if (entries > 30)
      break;
  }

  report << "```\n";
  return report.str();
}
