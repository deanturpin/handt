#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include <cassert>
#include <vector>

void unit_test() {

  // Test
  const std::vector<double> ascending1{1, 2, 3, 4, 5};
  const std::vector<double> ascending2{1, 2, 3, 4, 5, 6};
  const std::vector<double> ascending3{1, 2, 3};
  const std::vector<double> ascending4{1, 2};

  // Front/back end trim sizes
  assert(lft::front_end(ascending1).size() == 2 && "front end trimming fail");
  assert(lft::front_end(ascending2).size() == 3 && "front end trimming fail");
  assert(lft::back_end(ascending1).size() == 3 && "back end trimming fail");
  assert(lft::back_end(ascending2).size() == 3 && "back end trimming fail");

  // Min max
  assert(lft::maximum(ascending3) > 2.0);
  assert(lft::minimum(ascending3) < 2.0);

  // Front, back and mean (with some other containers)
  assert(lft::front(ascending4) < 2.0);
  assert(lft::back(ascending4) > 1.0);
  assert(lft::back(ascending4) > 1);
  assert(lft::mean(ascending4) > 1.0);

  // Primary strategies
  using cont2 = std::vector<double>;
  const auto &prim = lft::primary_strategies;

  // Always true
  assert(prim.front().first == "Indifferent");
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
  const auto &strat = lft::secondary_strategies;
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
  assert(lft::mean(test1) > 1.0); // 8 / 4 = 2
  assert(strat.at(3).second(test1) > 1.0);
  assert(strat.at(4).second(test1) < 2.26);
  assert(strat.at(5).second(test1) < .5);
  assert(strat.at(6).second(test1) < .9);
}

#endif
