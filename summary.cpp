#include <map>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include "position.h"
#include "utils.h"

auto get_positions(const std::string file) {

  std::vector<trade_position> positions;

  std::ifstream in(file);
  if (in.good()) {
    trade_position p;
    while (in >> p)
      positions.push_back(p);
  }

  return positions;
}

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
  std::map<std::string, double> ins, outs;
  for (const auto &pos : all) {
    const auto strategy = pos.strategy;
    ins[strategy] += 100.0;
    outs[strategy] += pos.yield;
  }

  // Individual strategy performance
  std::cout << "STRATEGY\tIN\tOUT\tRETURN (fees not included)\n";
  for (const auto &i : ins) {
    const std::string strategy = i.first;
    const double in = ins[strategy];
    const double out = outs[strategy];
    const double yield = 100.0 * out / in;

    std::cout << strategy << "\t"
      << in << "\t" << out << "\t" << yield << " %\n";
  }

  // Overall performance
  const double in_sum = std::accumulate(ins.cbegin(), ins.cend(), 0.0, []
                                        (auto sum, const auto &i){
                                        return sum + i.second;
                                        });

  const double out_sum = std::accumulate(outs.cbegin(), outs.cend(), 0.0, []
                                        (auto sum, const auto &i){
                                        return sum + i.second;
                                        });

  const double overall_yield = 100.0 * out_sum / in_sum;
  std::cout << "\n\t\t" << in_sum << "\t" << out_sum << "\t"
    << overall_yield << " %\n";
}
