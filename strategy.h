#ifndef STRATEGY
#define STRATEGY

#include <numeric>
#include <string>
#include <vector>

namespace lft {

// The original snooper
class snooper {

public:
  // The name of this strategy will be reported in the logs
  const std::string name = "snooper";

  // We can only create this strategy if we supply some prices
  explicit snooper(const std::vector<double> p) : prices(p) {
    spot = prices.back();
  }

  // Time to buy
  bool buy() const {
    const double average =
        std::accumulate(prices.cbegin(), prices.cend(), 0.0,
                        [](auto &sum, auto &i) { return sum + i; }) /
        prices.size();
    return average / spot > threshold;
  }

  // Time to sell
  bool sell(const double position) const { return spot / position > threshold; }

protected:
  // The prices upon which we shall make our decisions
  const std::vector<double> prices;

  // The threshold at which we make our decisions
  const double threshold = 1.05;

  // The current spot
  double spot;
};

// A snooper with higher expections
class snooper_grande : public snooper {

public:
  const std::string name = "snooper_grande";
  const double threshold = 1.1;

  explicit snooper_grande(const std::vector<double> p) : prices(p) {
    spot = prices.back();
  }
};
}

#endif
