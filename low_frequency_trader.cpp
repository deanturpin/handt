#include "low_frequency_trader.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <map>
#include <numeric>

// THE STRATEGIES - by Low Frequency Trader

// Strategy definition helper routines
const auto mean = [](const auto &p) constexpr {
  return std::accumulate(p.cbegin(), p.cend(), 0.0) / p.size();
};

const auto maximum = [](const auto &p) constexpr {
  return *std::max_element(p.cbegin(), p.cend());
};

const auto minimum = [](const auto &p) constexpr {
  return *std::min_element(p.cbegin(), p.cend());
};

// Front end size is rounded down by pushing the trim size upwards
const auto front_end = [](const auto &p) {
  const int trim = std::rint(std::ceil(p.size() / 2.0));
  return std::vector<double>{p.cbegin(), std::prev(p.cend(), trim)};
};

// Back end size is rounded up by pushing the trim size downwards
const auto back_end = [](const auto &p) {
  const int trim = std::rint(std::floor(p.size() / 2.0));
  return std::vector<double>{std::next(p.cbegin(), trim), p.cend()};
};

const auto front = [](const auto &p) { return p.front(); };
const auto back = [](const auto &p) { return p.back(); };

// Diffs between values
const auto diffs = [](const std::vector<double> &p) {

  // Calculate the diffs
  std::vector<double> d(p.size());
  std::adjacent_difference(p.begin(), p.end(), d.data());

  // Pop the large first value off the front (minimise copying)
  d.front() = d.back();
  d.pop_back();

  return d;
};

// Primary strategies are simple boolean tests
std::map<std::string, func1> primary_strategies{

    // Always return positively
    {std::string{"Indifferent"}, []([[maybe_unused]] cont p) {return true;}},

    // Return positively if trending upwards
    {"Leaping",
     [](cont p) {
       // Log upwards trend
       unsigned int trend = 0;
       for (const auto &d : diffs(p))
         if (d > 0.0)
           ++trend;

       return trend > p.size() / 2;
     }},

    // Return positively if trending downwards
    {"Supine",
     [](cont p) {
       // Log downwards trend
       unsigned int trend = 0;
       for (const auto &d : diffs(p))
         if (d < 0.0)
           ++trend;

       return trend > p.size() / 2;
     }},

    // Return positively if crossing a significant boundary
    {"Straddling",
     [](cont p) {
       const auto &[min, max] = std::minmax(p.front(), p.back());

       unsigned long threshold = 0;
       for (const unsigned long &mod : {1, 10, 100, 1000, 10000}) {

         const unsigned long test = max - std::llrint(max) % mod;

         if (test == 0)
           break;

         threshold = test;
       }

       return min < threshold && max > threshold;
     }},

    // Minimum comes before maximum
    {"Darting",
     [](cont p) {
       const auto &[min, max] = std::minmax_element(p.cbegin(), p.cend());
       return std::distance(p.cbegin(), min) < std::distance(p.cbegin(), max);
     }},

    // Maximum comes before minimum
    {"Slouching", [](cont p) {
       const auto &[min, max] = std::minmax_element(p.cbegin(), p.cend());
       return std::distance(p.cbegin(), min) > std::distance(p.cbegin(), max);
     }},
};

// Secondary strategies yield a buy threshold
std::map<std::string, func2> secondary_strategies{

    // Always succeed
    {"Lundehund", []([[maybe_unused]] cont p) constexpr {return 2.0;}},

    // Front/back
    {"Norrbottenspets", [](cont p) { return front(p) / back(p); }},
    {"Jagdterrier", [](cont p) { return back(p) / front(p); }},

    // Mean over front/back
    {"Xoloitzcuintli", [](cont p) { return mean(p) / back(p); }},
    {"Basenji", [](cont p) { return mean(p) / front(p); }},
    {"Sphynx", [](cont p) { return front(p) / mean(p); }},
    {"Affenpinscher", [](cont p) { return back(p) / mean(p); }},

    // Partial means
    {"Capybara", [](cont p) { return mean(front_end(p)) / mean(back_end(p)); }},
    {"Munchkin", [](cont p) { return mean(back_end(p)) / mean(front_end(p)); }},
    {"Badger", [](cont p) { return mean(p) / mean(back_end(p)); }},
    {"Bandicoot", [](cont p) { return mean(back_end(p)) / mean(p); }},

    // Min/max over back/front
    {"Mink", [](cont p) { return minimum(p) / back(p); }},
    {"Ocelot", [](cont p) { return minimum(p) / front(p); }},
    {"Griffon", [](cont p) { return maximum(p) / back(p); }},
    {"Cricket", [](cont p) { return maximum(p) / front(p); }},

    // Back/front over min/max
    {"Axolotl", [](cont p) { return back(p) / minimum(p); }},
    {"Shiba Inu", [](cont p) { return front(p) / minimum(p); }},
    {"Lowchen", [](cont p) { return back(p) / maximum(p); }},
    {"Narwahl", [](cont p) { return front(p) / maximum(p); }},

    // Min over max
    {"Bichon Frise", [](cont p) { return minimum(p) / maximum(p); }},
    {"Havanese", [](cont p) { return maximum(p) / minimum(p); }},

    // Min/max over mean
    {"Shih Tzu", [](cont p) { return minimum(p) / mean(p); }},
    {"Pomeranian", [](cont p) { return maximum(p) / mean(p); }},
    {"Pekingese", [](cont p) { return mean(p) / minimum(p); }},
    {"Papillon", [](cont p) { return mean(p) / maximum(p); }},
};

std::map<std::string, func1> get_primary_strategies() {
  return primary_strategies;
}

std::map<std::string, func2> get_secondary_strategies() {
  return secondary_strategies;
}

void lft_unit_test() {

  // Front/back end trim sizes
  const std::vector<double> ascending1{1, 2, 3, 4, 5};
  const std::vector<double> ascending2{1, 2, 3, 4, 5, 6};
  assert(front_end(ascending1).size() == 2 && "front end trimming fail");
  assert(front_end(ascending2).size() == 3 && "front end trimming fail");
  assert(back_end(ascending1).size() == 3 && "back end trimming fail");
  assert(back_end(ascending2).size() == 3 && "back end trimming fail");

  // Min/max
  const std::vector<double> ascending3{1, 2, 3};
  assert(maximum(ascending3) > 2.0);
  assert(minimum(ascending3) < 2.0);

  // Front, back and mean (with some other containers)
  const std::vector<double> ascending4{1, 2};
  assert(front(ascending4) < 2.0);
  assert(back(ascending4) > 1.0);
  assert(back(ascending4) > 1);
  assert(mean(ascending4) > 1.0);

  // Primary strategies
  assert(primary_strategies.size() == 6);
  assert(primary_strategies["Indifferent"]({1, 2, 3, 4, 5}) == true);
  assert(primary_strategies["Leaping"]({1, 2, 3, 4, 5}) == true);
  assert(primary_strategies["Leaping"]({5, 4, 3, 2, 1}) == false);
  assert(primary_strategies["Supine"]({1, 2, 3, 4, 5}) == false);
  assert(primary_strategies["Supine"]({5, 4, 3, 2, 1}) == true);
  assert(primary_strategies["Straddling"]({8, 9, 10, 11, 12}) == true);
  assert(primary_strategies["Straddling"]({10, 11, 12, 12}) == false);
  assert(primary_strategies["Straddling"]({87, 98, 99, 100}) == false);
  assert(primary_strategies["Straddling"]({87, 98, 99, 100, 101}) == true);
  assert(primary_strategies["Darting"]({1, 2, 3, 4, 5}) == true);
  assert(primary_strategies["Darting"]({5, 4, 3, 2, 1}) == false);
  assert(primary_strategies["Slouching"]({1, 2, 3, 4, 5}) == false);
  assert(primary_strategies["Slouching"]({5, 4, 3, 2, 1}) == true);

  // Secondary strategies
  assert(secondary_strategies.size() == 25);
  assert(secondary_strategies["Lundehund"]({1, 2, 3, 4, 5}) > 1.0);

  assert(secondary_strategies["Norrbottenspets"]({1, 2}) < 1.0);
  assert(secondary_strategies["Norrbottenspets"]({2, 1}) > 1.0);
  assert(secondary_strategies["Jagdterrier"]({1, 2}) > 1.0);
  assert(secondary_strategies["Jagdterrier"]({2, 1}) < 1.0);

  assert(secondary_strategies["Xoloitzcuintli"]({1, 1, 1, 10}) < 1.0);
  assert(secondary_strategies["Basenji"]({1, 1, 1, 10}) > 1.0);
  assert(secondary_strategies["Sphynx"]({10, 1, 1}) > 1.0);
  assert(secondary_strategies["Affenpinscher"]({10, 1, 1}) < 1.0);
}
