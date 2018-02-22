#ifndef LFT_STRATEGY
#define LFT_STRATEGY

#include <iostream>
#include <istream>
#include <memory>
#include <numeric>
#include <string>
#include <vector>

namespace lft {

// The top level base class
struct strategy {

  // A strategy needs a unique name
  const std::string name = "undefined";

  // A lengthy description
  const std::string description = "undefined";

  // And buy and sell routines that take a series of prices and return an
  // action: buy or sell
  virtual bool buy(const std::vector<double> &) const = 0;
  virtual bool sell(const std::vector<double> &, const double &) const = 0;
};

struct turbo : public strategy {
  const std::string name = "turbo_20";
  bool buy(const std::vector<double> &series) const override {
    const double average =
        std::accumulate(series.cbegin(), series.cend(), 0.0,
                        [](auto &sum, const auto &i) { return sum + i; }) /
        series.size();

    const double spot = series.back();
    return average / spot > 1.2;
  }
};

// Zim zimma
struct zimzimma : public turbo {
  const std::string name = "zimzimma";
  bool sell(const std::vector<double> &series,
            const double &buy_price) const override {
    double trend = 0.0;
    for (auto i = series.cbegin(); i != std::prev(series.cend()); ++i)
      trend += (*i < *std::next(i) ? 1.0 : -1.0);
    return trend > series.size() * .75;
  };
};

struct turbooo : public turbo {
  const std::string name = "turbooo";
};

// Create strategy library
std::vector<std::shared_ptr<strategy2>> strats{
    std::make_shared<turbo>(), std::make_shared<turbooo>(),
};
}

#endif
