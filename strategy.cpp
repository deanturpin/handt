#include "strategy.h"
#include <numeric>

// Generate all permutations of strategies and thresholds

std::vector<strategy_t> get_strategies() {

  // Create a set of thresholds to use with each buy strategy
  std::vector<int> thresholds(15);
  std::iota(thresholds.begin(), thresholds.end(), 3);

  // Get the strategies
  const auto &primary_strategies = get_primary_strategies();
  const auto &secondary_strategies = get_secondary_strategies();

  // Create and all strategy permutations up front
  const auto total_permutations = primary_strategies.size() *
                                  secondary_strategies.size() *
                                  thresholds.size();

  std::vector<strategy_t> strategies;
  strategies.reserve(total_permutations);

  // Populate with strategies from the handt library
  for (const auto &[name1, buy1] : primary_strategies)
    for (const auto &[name2, buy2] : secondary_strategies)
      for (const auto &threshold : thresholds)
        strategies.push_back(
            {name1 + '-' + name2 + '-' + std::to_string(threshold), buy1, buy2,
             threshold});

  return strategies;
}
