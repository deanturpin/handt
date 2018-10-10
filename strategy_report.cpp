#include "strategy_report.h"
#include <algorithm>
#include <sstream>
#include <string_view>

// Generate a summary of all strategies over all currency pairs

std::string get_strategy_report(const std::vector<backtest_t> &backtests) {

  std::stringstream report;

  struct perf {
    unsigned int good = 0;
    unsigned int bad = 0;
  };

  std::vector<std::pair<std::string, perf>> strategy_performance;

  for (const auto &b : backtests) {

    // Drop the threshold from the name
    std::string_view trimmed = b.name;
    trimmed.remove_suffix(trimmed.size() - trimmed.find_last_of("-"));

    // See if we have already have an entry for the current strategy
    auto it =
        std::find_if(strategy_performance.begin(), strategy_performance.end(),
                     [&trimmed](const auto &s) { return s.first == trimmed; });

    if (it == strategy_performance.end()) {
      strategy_performance.push_back({std::string{trimmed}, {}});
      it = std::prev(strategy_performance.end());
    }

    it->second.good += b.good_deals.size();
    it->second.bad += b.bad_deals.size();
  }

  // Sort backtests by success
  std::stable_sort(strategy_performance.begin(), strategy_performance.end(),
                   [](const auto &a, const auto &b) {
                     const double agd = a.second.good;
                     const double bgd = b.second.good;
                     const double abd = a.second.bad;
                     const double bbd = b.second.bad;

                     return (agd > 0.0 ? agd : .9) / (abd > 0.0 ? abd : .9) >
                            (bgd > 0.0 ? bgd : .9) / (bbd > 0.0 ? bbd : .9);
                   });

  report << strategy_performance.size() << " strategies\n";
  report << "```\n";
  unsigned int entries = 0;
  for (const auto &[name, performance] : strategy_performance) {
    report << name << ' ' << performance.good << '/' << performance.bad << '\n';

    ++entries;
    // if (entries > 30)
    //   break;
  }

  report << "```\n";
  return report.str();
}
