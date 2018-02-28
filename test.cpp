#include "strategy.h"
#include "utils.h"
#include <fstream>
#include <iostream>

int main() {

  // Get some example prices
  const std::map<std::string, std::vector<double>>  prices =
    get_prices("example.csv");

  // A place for the results
  std::stringstream results;

  // Test strategies on each series
  for (const auto &p : prices) {

    const auto &name = p.first;
    const auto &series = p.second;

    const auto buys = lft::run_strategies(series);
    results << name << "\t";
    for (const auto &buy : buys)
      results << buy << " ";
    results << "\n";
  }

  std::cout << results.str();
}
