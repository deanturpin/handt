#ifndef STRATEGY
#define STRATEGY

#include <numeric>
#include <string>
#include <vector>

// SNOOPER
// Trigger when spot is 10% below average for the period
// Don't track to bottom (could fall to zero)
// Sell when spot is 10% above lowest price
struct strategy {
  // strategy(){}
  const std::string name = "snooper";
  const double threshold = 1.1;
  bool buy(const std::vector<double> &p) const {
    const double spot = p.back();
    const double average =
        std::accumulate(p.cbegin(), p.cend(), 0.0,
                        [](auto &sum, auto &i) { return sum + i; }) /
        p.size();
    return average / spot > threshold;
  }

  bool sell(const double &spot, const double &position) const {
    return spot / position > threshold;
  }
};

// SNOOPER GRANDE
// Like SNOOPER but 15%
struct snooper_grande : strategy {
  const std::string name = "snooper_grande";
  const double threshold = 1.15;
};

// SNOOPER PEQUENO
// Like SNOOPER but 5%
struct snooper_pequeno : strategy {
  const std::string name = "snooper_pequeno";
  const double threshold = 1.15;
};

#endif
