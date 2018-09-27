#ifndef HANDT_H
#define HANDT_H

#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <numeric>
#include <vector>

namespace handt {

// The container passed throughout
using cont = const std::vector<double> &;

// Function definitions for the strategy types
using func1 = std::function<bool(cont)>;
using func2 = std::function<double(cont)>;

// Primary strategies are simple boolean tests
const std::vector<std::pair<std::string, func1>> primary_strategies{

    // Always return positively
    {"Crouching", []([[maybe_unused]] cont p) constexpr {return true;
} // namespace handt
}
,

    // Return positively if trending upwards
    {"Leaping",
     [](cont p) {
       unsigned int trend = 0;
       for (auto i = p.cbegin(); i != std::prev(p.cend()); ++i)
         if (*i < *std::next(i))
           ++trend;

       return trend > p.size() / 2;
     }},

    // Return positively if trending downwards
    {"Supine",
     [](cont p) {
       unsigned int trend = 0;
       for (auto i = p.cbegin(); i != std::prev(p.cend()); ++i)
         if (*i > *std::next(i))
           ++trend;

       return trend > p.size() / 2;
     }},

    // Return positively if crossing a significant boundary
    {"Straddling",
     [](cont p) {
       const auto &[min, max] = std::minmax(p.front(), p.back());

       unsigned long threshold = 0;
       for (const unsigned long &mod : {1, 10, 100, 1000, 10000}) {

         const unsigned long test =
             max - (static_cast<unsigned long>(max) % mod);

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
}
;

// Strategy definition helper routines
const auto mean = [](const auto &p) {
  return std::accumulate(p.cbegin(), p.cend(), 0.0) /
         static_cast<double>(p.size());
};

const auto maximum = [](const auto &p) {
  return *std::max_element(p.cbegin(), p.cend());
};

const auto minimum = [](const auto &p) {
  return *std::min_element(p.cbegin(), p.cend());
};

// Front end size is rounded down by pushing the trim size upwards
const auto front_end = [](const auto &p) {
  const size_t trim = std::ceil(p.size() / 2.0);
  return decltype(p){p.cbegin(), std::prev(p.cend(), trim)};
};

// Back end size is rounded up by pushing the trim size downwards
const auto back_end = [](const auto &p) {
  const size_t trim = std::floor(p.size() / 2.0);
  return decltype(p){std::next(p.cbegin(), trim), p.cend()};
};

const auto front = [](const auto &p) { return p.front(); };
const auto back = [](const auto &p) { return p.back(); };

// Secondary strategies yield a buy threshold
const std::vector<std::pair<std::string, func2>> secondary_strategies{

    // Always succeed
    {"Lundehund", []([[maybe_unused]] cont p) { return 2.0; }},

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

void unit_test() {

  // Test
  const std::vector<double> ascending1{1, 2, 3, 4, 5};
  const std::vector<double> ascending2{1, 2, 3, 4, 5, 6};
  const std::vector<double> ascending3{1, 2, 3};
  const std::vector<double> ascending4{1, 2};

  // Front/back end trim sizes
  assert(handt::front_end(ascending1).size() == 2);
  assert(handt::front_end(ascending2).size() == 3);
  assert(handt::back_end(ascending1).size() == 3);
  assert(handt::back_end(ascending2).size() == 3);

  // Min max
  assert(maximum(ascending3) > 2.0);
  assert(minimum(ascending3) < 2.0);

  // Front, back and mean (with some other containers)
  assert(front(ascending4) < 2.0);
  assert(back(ascending4) > 1.0);
  assert(back(ascending4) > 1);
  assert(mean(ascending4) > 1.0);

  // Primary strategies
  using cont2 = std::vector<double>;
  const auto &prim = primary_strategies;

  // Always true
  assert(prim.front().first == "Crouching");
  assert(prim.at(0).second(cont2{1, 2, 3, 4, 5}) == true);

  // Trending updwards
  assert(prim.at(1).second(cont2{1, 2, 3, 4, 5}) == true && "trending upwards");
  assert(prim.at(1).second(cont2{5, 4, 3, 2, 1}) == false);

  // Trending downwards
  assert(prim.at(2).second(cont2{1, 2, 3, 4, 5}) == false &&
         "trending downwards");
  assert(prim.at(2).second(cont2{5, 4, 3, 2, 1}) == true);

  // Straddling
  assert(prim.at(3).second(cont2{8, 9, 10, 11, 12}) == true);
  assert(prim.at(3).second(cont2{10, 11, 12, 12}) == false);
  assert(prim.at(3).second(cont2{87, 98, 99, 100}) == false);
  assert(prim.at(3).second(cont2{87, 98, 99, 100, 101}) == true);

  // Darting
  assert(prim.at(4).second(cont2{1, 2, 3, 4, 5}) == true);
  assert(prim.at(4).second(cont2{5, 4, 3, 2, 1}) == false);

  // Slouching
  assert(prim.at(5).second(cont2{1, 2, 3, 4, 5}) == false);
  assert(prim.at(5).second(cont2{5, 4, 3, 2, 1}) == true);

  // Secondary strategies
  const auto &strat = secondary_strategies;
  assert(strat.at(0).second(cont2{1, 2, 3, 4, 5}) > 1.0);
  assert(strat.at(0).second(cont2{}) > 1.0);

  // Front over back
  assert(strat.at(1).second(cont2{1.0, 2.0}) < 1.0);
  assert(strat.at(1).second(cont2{2.0, 1.0}) > 1.0);
  assert(strat.at(1).second(cont2{2.0, 2.0}) < 1.1);
  assert(strat.at(2).second(cont2{1.0, 2.0}) > 1.0);
  assert(strat.at(2).second(cont2{2.0, 1.0}) < 1.0);
  assert(std::isnan(strat.at(1).second(cont2{0.0, 0.0})));
  assert(std::isnan(strat.at(2).second(cont2{0.0, 0.0})));

  // Front/back over mean
  const std::vector<double> test1{1.0, 2.0, 4.0, 2.0};
  assert(mean(test1) > 1.0); // 8 / 4 = 2
  assert(strat.at(3).second(test1) > 1.0);
  assert(strat.at(4).second(test1) < 2.26);
  assert(strat.at(5).second(test1) < .5);
  assert(strat.at(6).second(test1) < .9);
}

} // namespace handt

#endif
