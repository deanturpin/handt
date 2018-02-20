#include <map>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include "position.h"

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

  // Get the buys
  const auto buys = get_positions("buys.csv");
  std::cout << buys.size() << " buys\n";

  // Get the sells
  const auto sells = get_positions("sells.csv");
  std::cout << sells.size() << " sells\n\n";

  // Consolidate all positions
  auto all = buys;
  all.insert(std::end(all), std::begin(sells), std::end(sells));

  // Close all positions
  std::map<std::string, double> ins, outs;
  for (const auto &pos : all) {

    const auto name = pos.strategy;
    const auto yield = pos.sell_price;

    ins[name] += 100.0;
    outs[name] += yield;
  }

  const double in_sum = std::accumulate(ins.cbegin(), ins.cend(), 0.0, []
                                        (auto sum, const auto &i){
                                          return sum + i.second;
                                        });

  const double out_sum = std::accumulate(outs.cbegin(), outs.cend(), 0.0, []
                                        (auto sum, const auto &i){
                                          return sum + i.second;
                                        });

  std::cout << "IN " << in_sum << "\n";
  for (const auto &i : ins) {
    const std::string strategy = i.first;
    const auto in = ins[strategy];
    const auto out = outs[strategy];

    std::cout << strategy << "\t" << in << "\t" << out << "\n";
  }
}
