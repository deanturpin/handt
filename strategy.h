#ifndef LFT_STRATEGY
#define LFT_STRATEGY

#include <algorithm>
#include <iostream>
#include <istream>
#include <memory>
#include <numeric>
#include <string>
#include <vector>

namespace lft {

// The top level base class
// A strategy needs a unique name, a description and a buy method
struct strategy {
  virtual std::string description() const = 0;
  virtual std::string name() const = 0;
  virtual bool buy(const std::vector<double> &) const = 0;
};

////////////////////////////////////////////////////////////////////////////////
// AVERAGE
////////////////////////////////////////////////////////////////////////////////

struct spot_average : public strategy {

  std::string description() const override { return
    "Buy when the spot is higher than the average for the period"; }

  std::string name() const override { return "spot_average"; }
  virtual double threshold() const { return 1.1; }

  bool buy(const std::vector<double> &series) const override {
    const double average =
        std::accumulate(series.cbegin(), series.cend(), 0.0,
                        [](auto &sum, const auto &i) { return sum + i; }) /
        series.size();

    const double spot = series.back();
    return average / spot > threshold();
  }
};

struct average_medium : public spot_average {
  std::string name() const override { return "spot_average_m"; }
  virtual double threshold() const { return 1.2; }
};

struct average_large : public spot_average {
  std::string name() const override { return "spot_average_l"; }
  virtual double threshold() const { return 1.3; }
};

struct average_xl : public spot_average {
  std::string name() const override { return "spot_average_xl"; }
  virtual double threshold() const { return 1.4; }
};

/*
////////////////////////////////////////////////////////////////////////////////
// SIM SIMMA
// Buy when the prices are mostly ascending
////////////////////////////////////////////////////////////////////////////////

struct simsimma : public average {
  std::string name() const override { return "simsimma"; }
  bool buy(const std::vector<double> &series) const override {
    double trend = 0.0;
    for (auto i = series.cbegin(); i != std::prev(series.cend()); ++i)
      trend += (*i < *std::next(i) ? 1.0 : -1.0);
    return trend > series.size() * .75;
  };
};

////////////////////////////////////////////////////////////////////////////////
// KOSOVICH
////////////////////////////////////////////////////////////////////////////////

struct kosovich : public average {
  std::string name() const override { return "kossages"; }
  bool buy(const std::vector<double> &series) const override {
    const double high = *std::max_element(series.cbegin(), series.cend());
    const double spot = series.back();
    return spot / high > 1.1;
  }
};

// Manual buy and auto exit
struct manual_buy : public turbo {
  std::string name() const override { return "manualxx"; }
  bool buy(const std::vector<double> &series) const override {
    static_cast<void>(series);
    return false;
  }
};

// NINO - don't consider small value coins
struct nino : public turbo {
  std::string name() const override { return "nino1000"; }
  virtual double threshold() const { return 1.2; }
  bool buy(const std::vector<double> &series) const override {
    const double spot = series.back();
    return spot < 10 ? false : turbo::buy(series);
  }
};

struct nino_min : public nino {
  std::string name() const override { return "nino1001"; }
  virtual double threshold() const { return 1.1; }
};

struct nino_max : public nino {
  std::string name() const override { return "nino1003"; }
  virtual double threshold() const { return 1.3; }
};

struct jk : public turbo {
  std::string name() const override { return "jkrise10"; }
  bool buy(const std::vector<double> &series) const override {
    const double average =
        std::accumulate(series.cbegin(), series.cend(), 0.0,
                        [](auto &sum, auto &i) { return sum + i; }) /
        series.size();
    const double spot = series.back();
    return spot / average > 1.1;
  }
};

struct jk_step : public turbo {
  std::string name() const override { return "jkstep20"; }
  bool buy(const std::vector<double> &series) const override {
    const unsigned long mid = series.size() / 2;
    const double back =
        std::accumulate(series.cbegin(), std::next(series.cbegin(), mid), 0.0,
                        [](auto &sum, auto &i) { return sum + i; });
    const double front =
        std::accumulate(series.crbegin(), std::next(series.crbegin(), mid), 0.0,
                        [](auto &sum, auto &i) { return sum + i; });
    return front / back > 1.2;
  }
};

struct bisect : public turbo {
  std::string name() const override { return "bisect20"; }
  virtual double threshold() const { return 1.2; }
  bool buy(const std::vector<double> &series) const override {
    const double spot = series.back();

    // if (spot < 10)
      // return false;

    const unsigned long mid = series.size() / 2;
    const double back =
        std::accumulate(series.cbegin(), std::next(series.cbegin(), mid), 0.0,
                        [](auto &sum, auto &i) { return sum + i; }) /
        mid;
    const double front =
        std::accumulate(series.crbegin(), std::next(series.crbegin(), mid), 0.0,
                        [](auto &sum, auto &i) { return sum + i; }) /
        mid;

    return front / back > threshold();
  };
};

struct bigcap_low : public bigcap {
  std::string name() const override { return "bigcap10"; }
  double threshold() const override { return 1.1; }
};

struct rolling_average : public turbo {
  virtual unsigned long filter_length() const { return 20UL; }
  std::string name() const override { return "rolav20a"; }
  bool buy(const std::vector<double> &series) const override {
    const auto start = series.cbegin();
    const auto end = std::prev(series.cend(), filter_length());
    const auto filt = filter_length();
    std::vector<double> raverage;
    std::transform(start, end, std::back_inserter(raverage),
                   [&filt](const auto &i) {
                     const auto start = &i;
                     const auto end = std::next(&i, filt);
                     return std::accumulate(start, end, 0.0) / filt;
                   });

    return series.back() / raverage.back() > 1.05;
  };
};

// Rolling average over fewer points
struct rolling_average_short : public rolling_average {
  std::string name() const override { return "rolav10a"; }
  unsigned long filter_length() const override { return 10UL; }
};

// Ski slope profiles
struct ski_sunday : public turbo {
  std::string name() const override { return "skisun20"; }
  virtual double threshold() const { return 1.2; }
  bool buy(const std::vector<double> &series) const override {

    const unsigned long mid = series.size() / 2;
    const double back =
        std::accumulate(series.begin(), std::next(series.begin(), mid), 0.0,
                        [](auto &s, auto &i) { return s + i; }) / mid;

    const double front =
        std::accumulate(series.rbegin(), std::next(series.rbegin(), mid), 0.0,
                        [](auto &s, auto &i) { return s + i; }) / mid;

    const auto spot = series.back();
    return (back / front > threshold() && spot / front > 1.05);
  };
};

struct ski_sunday_low : public ski_sunday {
  std::string name() const override { return "skisun10"; }
  double threshold() const override { return 1.1; }
};

struct ski_sunday_vlow : public ski_sunday {
  std::string name() const override { return "skisun05"; }
  double threshold() const override { return 1.05; }
};

// Average comparison
struct average_compare : public turbo {
  std::string name() const override { return "jklongav"; }
  virtual unsigned long ratio() const { return 2; }
  bool buy(const std::vector<double> &series) const override {
    {
      const unsigned long mid = series.size() / ratio();
      const double recent_average =
          std::accumulate(std::next(series.cbegin(), mid), series.cend(), 0.0,
                          [](auto &sum, auto &i) { return sum + i; }) /
          mid;
      const double distant_average =
          std::accumulate(series.cbegin(), series.cend(), 0.0,
                          [](auto &sum, auto &i) { return sum + i; }) /
          series.size();

      return recent_average > distant_average;
    }
  }
};

struct average_compare3 : public turbo {
  std::string name() const override { return "jklonga3"; }
  virtual unsigned long ratio() const { return 3; }
};

struct average_compare4 : public turbo {
  std::string name() const override { return "jklonga4"; }
  virtual unsigned long ratio() const { return 3; }
};

// Create strategy library
const std::vector<std::shared_ptr<strategy>> strategy_library{
    // std::make_shared<turbo>(),
    // std::make_shared<turbo_short>(),
    // std::make_shared<turbo_long>(),
    // std::make_shared<simsimma>(),
    // std::make_shared<kos>(),
    // std::make_shared<nino>(),
    // std::make_shared<nino_min>(),
    // std::make_shared<nino_max>(),
    // std::make_shared<manual_buy>(),
    // std::make_shared<jk>(),
    // std::make_shared<jk_step>(),
    // std::make_shared<bigcap>(),
    // std::make_shared<bigcap_low>(),
    // std::make_shared<rolling_average>(),
    // std::make_shared<rolling_average_short>(),
    // std::make_shared<ski_sunday>(),
    // std::make_shared<ski_sunday_low>(),
    // std::make_shared<ski_sunday_vlow>(),
    // std::make_shared<average_compare>(),
    // std::make_shared<average_compare3>(),
    // std::make_shared<average_compare4>(),
};

*/

// Create strategy library
const std::vector<std::shared_ptr<strategy>> strategy_library{
  std::make_unique<spot_average>(),
  std::make_unique<average_medium>(),
  std::make_unique<average_large>(),
  std::make_unique<average_xl>(),
};

}

#endif
