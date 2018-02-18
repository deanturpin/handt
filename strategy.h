#ifndef STRATEGY
#define STRATEGY

#include <iostream>
#include <istream>
#include <numeric>
#include <string>
#include <vector>

// SNOOPER
// Trigger when spot is 10% below average for the period
// Don't track to bottom (could fall to zero)
// Sell when spot is 10% above lowest price
struct strategy {
  const std::string name = "snooper";
  const double threshold = 1.15;
  bool buy(const std::vector<double> &p) const {
    const double spot = p.back();
    const double average =
        std::accumulate(p.cbegin(), p.cend(), 0.0,
                        [](auto &sum, auto &i) { return sum + i; }) /
        p.size();
    return average / spot > threshold;
  }

  bool sell(const std::vector<double> &series, const double &buy) const {
    const auto sell = series.back();
    return sell / buy > threshold;
  }
};

// ALWAYS
// Always buy, always sell
struct always : strategy {
  const std::string name = "always";
  bool buy(const std::vector<double> &p) const {
    static_cast<void>(p);
    return true;
  }
  bool sell(const double &position, const double &spot) const {
    static_cast<void>(position);
    static_cast<void>(spot);
    return true;
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
  const double threshold = 1.05;
};

// SNOOPEROO
// Like SNOOPER but 2%
struct snooperoo : strategy {
  const std::string name = "snooperoo";
  const double threshold = 1.02;
};

#endif
