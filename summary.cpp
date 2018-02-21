#include "position.h"
#include "utils.h"
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

int main() {

  // Get the coins
  const auto prices = get_prices();
  std::cout << prices.size() << " coins analysed\n";

  // Get the buys
  const auto buys = get_positions("buys.csv");
  std::cout << buys.size() << " positions held\n";

  // Get the sells
  const auto sells = get_positions("sells.csv");
  std::cout << sells.size() << " complete transactions\n\n";

  // Consolidate all positions
  auto all = buys;
  all.insert(std::end(all), std::begin(sells), std::end(sells));

  // Close all positions
  std::map<std::string, double> ins, outs, durations, trades;
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
    const double yield = 100.0 * out / in;
    const double hours = (durations[strategy] / trades[strategy]) / 3600;

    std::cout << strategy << std::fixed << " " << yield << "\t" << in << "\t"
              << out << "\t" << hours << "\n";
  }

  // Overall performance
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
}
