// #include "strategy.h"
#include "position.h"
#include "utils.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <istream>
#include <iterator>
#include <memory>
#include <numeric>
#include <string>
#include <vector>

namespace lft {

// The top level base class
struct strategy {

  // A strategy needs a unique name
  virtual std::string name() const { return "undefined"; }

  // A lengthy description
  virtual std::string keywords() const { return "strategy"; }

  // And buy and sell routines that take a series of prices and return an
  // action: buy or sell
  virtual bool buy(const std::vector<double> &) const = 0;
  virtual bool sell(const std::vector<double> &, const double &) const = 0;
};

struct turbo : public strategy {
  std::string name() const override { return "turbo_20"; }
  std::string keywords() const override { return "average"; }
  bool buy(const std::vector<double> &series) const override {
    const double spot = series.back();
    const double average =
        std::accumulate(series.cbegin(), series.cend(), 0.0,
                        [](auto &sum, const auto &i) { return sum + i; }) /
        series.size();
    return average / spot > 1.2;
  }

  virtual bool sell(const std::vector<double> &series,
                    const double &buy_price) const override {
    // Otherwise check if we're happy with the return
    const auto sell_price = series.back();
    return sell_price / buy_price > 1.1;
  };
};

// Sim simma
struct simsimma : public turbo {
  std::string name() const override { return "simsimma"; }
  std::string keywords() const override { return "average"; }
  bool buy(const std::vector<double> &series) const override {
    double trend = 0.0;
    for (auto i = series.cbegin(); i != std::prev(series.cend()); ++i)
      trend += (*i < *std::next(i) ? 1.0 : -1.0);
    return trend > series.size() * .75;
  };
};

// Kos
struct kos : public turbo {
  std::string name() const override { return "kossages"; }
  std::string keywords() const override { return "peak"; }
  bool buy(const std::vector<double> &series) const override {
    const double high = *std::max_element(series.cbegin(), series.cend());
    const double spot = series.back();
    return spot / high > 1.1;
  }
};

// Manual buy and auto exit
struct manual_buy : public turbo {
  std::string name() const override { return "manualxx"; }
  std::string keywords() const override { return "manual"; }
  bool buy(const std::vector<double> &series) const override {
    static_cast<void>(series);
    return false;
  }
};

// Nino
struct nino : public turbo {
  std::string name() const override { return "nino1000"; }
  std::string keywords() const override { return "spike"; }
  bool buy(const std::vector<double> &series) const override {
        // Don't consider small value coins
        const double spot = series.back();
        if (spot < 10)
          return false;

        // Buy if the spot is significantly above the average
        const double average =
            std::accumulate(series.cbegin(), series.cend(), 0.0,
                            [](auto &sum, const auto &i) { return sum + i; }) /
            series.size();
        return average / spot > 1.2;
  }
};

struct nino_min : public nino {
  std::string name() const override { return "nino1001"; }
  bool buy(const std::vector<double> &series) const override {
        // Don't consider small value coins
        const double spot = series.back();
        if (spot < 10)
          return false;

        // Buy if the spot is significantly above the average
        const double average =
            std::accumulate(series.cbegin(), series.cend(), 0.0,
                            [](auto &sum, const auto &i) { return sum + i; }) /
            series.size();
        return average / spot > 1.1;
  }
};

struct nino_max : public nino {
  std::string name() const override { return "nino1003"; }
  bool buy(const std::vector<double> &series) const override {
        // Don't consider small value coins
        const double spot = series.back();
        if (spot < 10)
          return false;

        // Buy if the spot is significantly above the average
        const double average =
            std::accumulate(series.cbegin(), series.cend(), 0.0,
                            [](auto &sum, const auto &i) { return sum + i; }) /
            series.size();
        return average / spot > 1.3;
  }
};

struct jk : public turbo {
  std::string name() const override { return "jkrise10"; }
  std::string keywords() const override { return "average"; }
  bool buy(const std::vector<double> &series) const override {
        const double average =
            std::accumulate(series.cbegin(), series.cend(), 0.0,
                            [](auto &sum, auto &i) { return sum + i; }) /
            series.size();
        const double spot = series.back();
        return spot / average > 1.1;
  }
  virtual bool sell(const std::vector<double> &series,
                    const double &buy_price) const override {
        return series.back() / buy_price > 1.1;
  };
};

struct jk_step : public turbo {
  std::string name() const override { return "jkstep20"; }
  std::string keywords() const override { return "average"; }
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

struct bigcap : public turbo {
  std::string name() const override { return "bigcap20"; }
  std::string keywords() const override { return "average"; }
  virtual double threshold() const { return 1.2; }
  bool buy(const std::vector<double> &series) const override {
        const double spot = series.back();
        if (spot < 10)
          return false;

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
        // const auto length = series.size() - filter_length();
        const auto filt = filter_length();
        std::vector<double> raverage;
        std::transform(
            start, end, std::back_inserter(raverage), [&filt](const auto &i) {
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
struct ski_sunday : public bigcap {
  std::string name() const override { return "skisun20"; }
  virtual double threshold() const { return 1.2; }
  bool buy(const std::vector<double> &series) const override {
        if (series.back() < 10)
          return false;

        const unsigned long mid = series.size() / 2;

        const double back =
            std::accumulate(series.begin(), std::next(series.begin(), mid), 0.0,
                            [](auto &sum, auto &i) { return sum + i; }) /
            mid;

        const double front =
            std::accumulate(series.rbegin(), std::next(series.rbegin(), mid), 0.0,
                            [](auto &sum, auto &i) { return sum + i; }) /
            mid;

        const auto spot = series.back();
        return (back / front > threshold() && spot / front > 1.05);
      };
  };

struct ski_sunday_low : public ski_sunday {
  std::string name() const override { return "skisun10"; }
  double threshold() const override { return 1.1; }
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
std::vector<std::shared_ptr<strategy>> strategy_library{
    std::make_shared<turbo>(),
    std::make_shared<simsimma>(),
    std::make_shared<kos>(),
    std::make_shared<nino>(),
    std::make_shared<nino_min>(),
    std::make_shared<nino_max>(),
    std::make_shared<manual_buy>(),
    std::make_shared<jk>(),
    std::make_shared<jk_step>(),
    std::make_shared<bigcap>(),
    std::make_shared<bigcap_low>(),
    std::make_shared<rolling_average>(),
    std::make_shared<rolling_average_short>(),
    std::make_shared<ski_sunday>(),
    std::make_shared<ski_sunday_low>(),
    std::make_shared<average_compare>(),
    std::make_shared<average_compare3>(),
    std::make_shared<average_compare4>(),
};
}

// Let's trade
int main() {

  const auto &strategies = lft::strategy_library;

  for (const auto &s : strategies)
    std::cout << s->name() << "\n";

  // Get some recent prices
  auto prices = get_prices();

  // Containers for initial and ultimate positions
  std::vector<trade_position> positions;
  std::vector<trade_position> buys, sells;

  const std::string buy_file = "buys.csv";
  std::ifstream in(buy_file);
  if (in.good()) {
    trade_position p;
    while (in >> p)
      positions.push_back(p);
  }

  // Review all open positions
  for (auto &p : positions) {

    // Create a copy of the position
    auto &pos = p;

    // Try to find some prices for this currency
    const auto it =
        std::find_if(prices.cbegin(), prices.cend(), [&pos](const auto &coin) {
          return coin.first == pos.name;
        });

    if (it != prices.cend()) {

      pos.notes = "okprices";

      // Update position with latest info
      pos.sell_price = it->second.back();
      pos.duration = timestamp() - pos.timestamp;
      pos.yield = 100.0 * pos.sell_price / pos.buy_price;

      // Find the strategy for this position

      static auto strat_it = strategies.cbegin();
      find_if(strategies.cbegin(), strategies.cend(),
              [&pos](const auto &s) { return pos.strategy == s->name(); });

      // Found strategy, review position
      if (strat_it != strategies.cend()) {
        const auto &series = it->second;

        // Check if it's good to sell, otherwise push it back onto the buy list
        (*strat_it)->sell(series, pos.buy_price) ? sells.push_back(pos)
                                              : buys.push_back(pos);
      }

      // No strategy
      else {
        pos.notes = "undefine";
        buys.push_back(pos);
      }
    } else {
      pos.notes = "noprices";
      buys.push_back(pos);
    }
  }

  // Consolidate existing position and look for new ones
  for (const auto &coin : prices) {
    for (const auto &strat : strategies) {

      const std::string name = coin.first;
      const double spot = coin.second.back();
      const auto series = coin.second;

      // Check if we already hold a position on this currency with the current
      // strategy
      const auto it = std::find_if(
          positions.cbegin(), positions.cend(), [&name, &strat](const auto &p) {
            return p.name == name && p.strategy == strat->name();
          });

      // Check we don't already hold a position in this currency, if not
      // consider creating one
      if (it == positions.cend()) {
        if (strat->buy(series)) {
          trade_position pos;
          pos.name = name;

          // Initialise buy and sell to same price
          pos.buy_price = pos.sell_price = spot;

          pos.strategy = strat->name();
          pos.yield = 100.0 * pos.sell_price / pos.buy_price;

          // Initialise timestamps to the same time, sell will be updated each
          // time it is reviewed
          pos.timestamp = timestamp();
          pos.duration = 1;

          buys.push_back(pos);
        }
      }
    }
  }

  // Trading session is complete, write out current positions sorted by yield
  std::ofstream out(buy_file);
  std::sort(buys.begin(), buys.end(),
            [](const auto &a, const auto &b) { return a.yield < b.yield; });

  for (const auto &p : buys)
    out << p;
  out.close();

  // And append our successes
  out.open("sells.csv", std::ios::app);
  for (const auto &p : sells)
    out << p;
}
