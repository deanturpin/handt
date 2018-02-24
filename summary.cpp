#include "position.h"
#include "strategy.h"
#include "utils.h"
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

int main() {

  // Get the strategies
  const auto &strategies = lft::strategy_library;

  // Get the coins
  const auto prices = get_prices();
  std::cout << strategies.size() << " strategies have the opportunity to trade "
    << prices.size() << " coins every two minutes\n";
  std::cout << strategies.size() * prices.size() * 30 * 24
    << " decisions per day\n";

  // Get the buys
  const std::vector<trade_position> buys(get_positions("buys.csv"));
  std::cout << buys.size() << " positions held\n";

  // Get the sells
  const std::vector<trade_position> sells(get_positions("sells.csv"));
  std::cout << sells.size() << " complete trades\n\n";

  // Consolidate all positions
  auto all = buys;
  // all.insert(std::end(all), std::begin(sells), std::end(sells));

  // Initialise results with all strategies
  std::map<std::string, double> ins, outs, durations, trades;
  for (const auto &strategy : strategies) {
    const auto name = strategy->name();
    ins[name] = 0.0;
    outs[name] = 0.0;
    durations[name] = 0.0;
    trades[name] = 0.0;
  }

  // Close all positions
  for (const auto &pos : all) {
    const auto strategy = pos.strategy;
    ins[strategy] += 100.0;
    outs[strategy] += pos.yield;
    durations[strategy] += pos.duration;
    ++trades[strategy];
  }

  // Individual strategy performance
  std::cout << "STRATEGY % RETURN\t$ IN\t\t$ OUT\t\tDURATION (hrs)\t \n\n";
  for (const auto &i : ins) {
    const std::string strategy = i.first;
    const double in = ins[strategy];
    const double out = outs[strategy];
    const double yield = 100.0 * out / (in > 0 ? in : 1);
    const double hours =
        (durations[strategy] / (trades[strategy] > 0 ? trades[strategy] : 1)) /
        3600;

    std::cout << strategy << std::fixed << " " << yield << "\t" << in << "\t"
              << out << "\t" << hours << "\n";
  }

  // Strategy summary
  const double in_sum =
      std::accumulate(ins.cbegin(), ins.cend(), 0.0,
                      [](auto sum, const auto &i) { return sum + i.second; });

  const double out_sum =
      std::accumulate(outs.cbegin(), outs.cend(), 0.0,
                      [](auto sum, const auto &i) { return sum + i.second; });

  const double overall_yield = 100.0 * out_sum / in_sum;
  std::cout << "\nTOTAL    " << overall_yield << "\t" << in_sum << "\t"
            << out_sum << "\t\t\t"
            << "\n";

  // Individual coin performance
  // std::map<std::string, std::vector<double>>;
}
