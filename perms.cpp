#include "perms.h"
#include "strategy.h"

std::vector<strategy_t> get_strategies() {

  // Create a set of thresholds to use with each buy strategy
  std::vector<int> thresholds(22);
  std::iota(thresholds.begin(), thresholds.end(), 2);

  // Create and all strategy permutations up front
  const auto total_permutations = lft::primary_strategies.size() *
                                  lft::secondary_strategies.size() *
                                  thresholds.size();

  std::vector<strategy_t> permutations;
  permutations.reserve(total_permutations);

  // Populate with strategies from the handt library
  for (const auto &[name1, buy1] : lft::primary_strategies)
    for (const auto &[name2, buy2] : lft::secondary_strategies)
      for (const auto &threshold : thresholds)
        permutations.push_back(
            {name1 + '-' + name2 + '-' + std::to_string(threshold), buy1, buy2,
             threshold});

  return permutations;
}
