#include "position.h"
#include "utils.h"
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <istream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

// Let's trade
int main() {

  // A template strategy
  struct strategy {

    std::string name = "turbo_20";

    // BUY
    std::function<bool(const std::vector<double> &p)> buy = [&](const auto &p) {
      const double spot = p.back();
      const double average =
          std::accumulate(p.cbegin(), p.cend(), 0.0,
                          [](auto &sum, const auto &i) { return sum + i; }) /
          p.size();
      return average / spot > 1.2;
    };

    // SELL
    std::function<bool(const std::vector<double> &series,
                       const double &buy_price)>
        sell = [&](const auto &series, const auto &buy_price) {
          // Otherwise check if we're happy with the return
          const auto sell_price = series.back();
          return sell_price / buy_price > 1.1;
        };
  };

  // Define some strategies by creating the template and then overriding
  // accordingly
  std::vector<strategy> strategies;
  {
    // Original and best
    strategy s1;
    strategies.push_back(s1);

    {
      // Buy if the spot is a percentage above the average for the period
      strategy nino;
      nino.name = "nino1000";

      // Buy
      nino.buy = [&](const auto &p) {
        // Don't consider small value coins
        const double spot = p.back();
        if (spot < 10)
          return false;

        // Buy if the spot is significantly above the average
        const double average =
            std::accumulate(p.cbegin(), p.cend(), 0.0,
                            [](auto &sum, const auto &i) { return sum + i; }) /
            p.size();
        return average / spot > 1.2;
      };

      strategies.push_back(nino);
    }
    {
      strategy nino;
      nino.name = "manualxx";

      // Manual buy
      nino.buy = [&](const auto &p) {
        static_cast<void>(p);
        return false;
      };

      strategies.push_back(nino);
    }

    {
      // Buy if the spot is a percentage above the average for the period
      strategy nino;
      nino.name = "nino1001";

      // Buy
      nino.buy = [&](const auto &p) {
        // Don't consider small value coins
        const double spot = p.back();
        if (spot < 10)
          return false;

        // Buy if the spot is significantly above the average
        const double average =
            std::accumulate(p.cbegin(), p.cend(), 0.0,
                            [](auto &sum, const auto &i) { return sum + i; }) /
            p.size();
        return average / spot > 1.1;
      };

      strategies.push_back(nino);
    }
    {
      // Buy if the spot is a percentage above the average for the period
      strategy jk;
      jk.name = "jkrise10";

      // Buy
      jk.buy = [&](const auto &p) {
        const double spot = p.back();
        const double average =
            std::accumulate(p.cbegin(), p.cend(), 0.0,
                            [](auto &sum, auto &i) { return sum + i; }) /
            p.size();
        return spot / average > 1.1;
      };

      // Sell
      jk.sell = [&](const auto &series, const auto &buy_price) {
        return series.back() / buy_price > 1.1;
      };

      strategies.push_back(jk);
    }

    {
      strategy jk;
      jk.name = "jkstep20";

      // Buy
      jk.buy = [&](const auto &p) {

        const unsigned long mid = p.size() / 2;

        const double back =
            std::accumulate(p.cbegin(), std::next(p.cbegin(), mid), 0.0,
                            [](auto &sum, auto &i) { return sum + i; });

        const double front =
            std::accumulate(p.crbegin(), std::next(p.crbegin(), mid), 0.0,
                            [](auto &sum, auto &i) { return sum + i; });

        return front / back > 1.2;
      };

      // Sell
      jk.sell = [&](const auto &series, const auto &buy_price) {
        return series.back() / buy_price > 1.1;
      };

      strategies.push_back(jk);
    }

    {
      strategy jk;
      jk.name = "bigcap20";

      // Buy
      jk.buy = [&](const auto &p) {

        // Don't consider small value coins
        const double spot = p.back();
        if (spot < 10)
          return false;

        const unsigned long mid = p.size() / 2;
        const double back =
            std::accumulate(p.cbegin(), std::next(p.cbegin(), mid), 0.0,
                            [](auto &sum, auto &i) { return sum + i; }) /
            mid;
        const double front =
            std::accumulate(p.crbegin(), std::next(p.crbegin(), mid), 0.0,
                            [](auto &sum, auto &i) { return sum + i; }) /
            mid;

        return front / back > 1.20;
      };

      // Sell
      jk.sell = [&](const auto &series, const auto &buy_price) {
        return series.back() / buy_price > 1.1;
      };

      strategies.push_back(jk);
    }

    {
      strategy jk;
      jk.name = "bigcap10";

      // Buy
      jk.buy = [&](const auto &p) {

        if (p.back() < 10)
          return false;

        const unsigned long mid = p.size() / 2;

        // Calculate average of first half
        const double back =
            std::accumulate(p.begin(), std::next(p.begin(), mid), 0.0,
                            [](auto &sum, auto &i) { return sum + i; }) /
            mid;

        // Calculate average of second half
        const double front =
            std::accumulate(p.rbegin(), std::next(p.rbegin(), mid), 0.0,
                            [](auto &sum, auto &i) { return sum + i; }) /
            mid;

        return front / back > 1.10;
      };

      // Sell
      jk.sell = [&](const auto &series, const auto &buy_price) {
        return series.back() / buy_price > 1.1;
      };

      strategies.push_back(jk);
    }

    {
      // Ski slope shape, no small caps
      strategy jk;
      jk.name = "skisun05";

      jk.buy = [&](const auto &p) {

        if (p.back() < 10)
          return false;

        const unsigned long mid = p.size() / 2;

        const double back =
            std::accumulate(p.begin(), std::next(p.begin(), mid), 0.0,
                            [](auto &sum, auto &i) { return sum + i; }) /
            mid;

        const double front =
            std::accumulate(p.rbegin(), std::next(p.rbegin(), mid), 0.0,
                            [](auto &sum, auto &i) { return sum + i; }) /
            mid;

        const auto spot = p.back();
        return (back / front > 1.10 && spot / front > 1.05);
      };

      // Sell
      jk.sell = [&](const auto &series, const auto &buy_price) {
        return series.back() / buy_price > 1.1;
      };

      strategies.push_back(jk);
    }

    {
      // Ski slope shape, no small caps
      strategy jk;
      jk.name = "skisun20";

      jk.buy = [&](const auto &p) {

        if (p.back() < 10)
          return false;

        const unsigned long mid = p.size() / 2;

        const double back =
            std::accumulate(p.begin(), std::next(p.begin(), mid), 0.0,
                            [](auto &sum, auto &i) { return sum + i; }) /
            mid;

        const double front =
            std::accumulate(p.rbegin(), std::next(p.rbegin(), mid), 0.0,
                            [](auto &sum, auto &i) { return sum + i; }) /
            mid;

        const auto spot = p.back();
        return (back / front > 1.20 && spot / front > 1.05);
      };

      // Sell
      jk.sell = [&](const auto &series, const auto &buy_price) {
        return series.back() / buy_price > 1.1;
      };

      strategies.push_back(jk);
    }

    {
      strategy jk;
      jk.name = "jklonga3";

      jk.buy = [&](const auto &series) {

        const unsigned long mid = series.size() / 3;
        const double recent_average =
            std::accumulate(std::next(series.cbegin(), mid), series.cend(), 0.0,
                            [](auto &sum, auto &i) { return sum + i; }) /
            mid;
        const double distant_average =
            std::accumulate(series.cbegin(), series.cend(), 0.0,
                            [](auto &sum, auto &i) { return sum + i; }) /
            series.size();

        return recent_average > distant_average;
      };

      strategies.push_back(jk);
    }

    {
      strategy jk;
      jk.name = "jklongav";

      jk.buy = [&](const auto &series) {

        const unsigned long mid = series.size() / 2;
        const double recent_average =
            std::accumulate(std::next(series.cbegin(), mid), series.cend(), 0.0,
                            [](auto &sum, auto &i) { return sum + i; }) /
            mid;
        const double distant_average =
            std::accumulate(series.cbegin(), series.cend(), 0.0,
                            [](auto &sum, auto &i) { return sum + i; }) /
            series.size();

        return recent_average > distant_average;
      };

      strategies.push_back(jk);
    }
    {
      // Construct rolling average series, buy if significant excursion
      strategy jk;
      jk.name = "rolav10a";

      jk.buy = [&](const auto &series) {

        const unsigned long filter_length = 10;
        const auto start = series.cbegin();
        const auto end = std::prev(series.cend(), filter_length);
        const auto length = series.size() - filter_length;

        std::vector<double> raverage;
        std::transform(
            start, end, std::back_inserter(raverage), [&length](const auto &i) {
              const auto start = &i;
              const auto end = std::next(&i, filter_length);
              return std::accumulate(start, end, 0.0) / filter_length;
            });

        return series.back() / raverage.back() > 1.05;
      };

      strategies.push_back(jk);
    }
    {
      // Construct rolling average series, buy if significant excursion
      strategy jk;
      jk.name = "rolav20a";

      jk.buy = [&](const auto &series) {

        const unsigned long filter_length = 20;
        const auto start = series.cbegin();
        const auto end = std::prev(series.cend(), filter_length);
        const auto length = series.size() - filter_length;

        std::vector<double> raverage;
        std::transform(
            start, end, std::back_inserter(raverage), [&length](const auto &i) {
              const auto start = &i;
              const auto end = std::next(&i, filter_length);
              return std::accumulate(start, end, 0.0) / filter_length;
            });

        return series.back() / raverage.back() > 1.05;
      };

      strategies.push_back(jk);
    }
    {
      // Buy if the spot exceeds the recent max significantly
      strategy kos;
      kos.name = "koskos10";

      kos.buy = [&](const auto &series) {
        const double high = *std::max_element(series.cbegin(), series.cend());
        const double spot = series.back();

        return spot / high > 1.1;
      };

      strategies.push_back(kos);
    }
  }

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
              [&pos](const auto &s) { return pos.strategy == s.name; });

      // Found strategy, review position
      if (strat_it != strategies.cend()) {
        const auto &series = it->second;

        // Check if it's good to sell, otherwise push it back onto the buy list
        strat_it->sell(series, pos.buy_price) ? sells.push_back(pos)
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
            return p.name == name && p.strategy == strat.name;
          });

      // Check we don't already hold a position in this currency, if not
      // consider creating one
      if (it == positions.cend()) {
        if (strat.buy(series)) {
          trade_position pos;
          pos.name = name;

          // Initialise buy and sell to same price
          pos.buy_price = pos.sell_price = spot;

          pos.strategy = strat.name;
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
