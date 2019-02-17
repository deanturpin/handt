#ifndef LFT_H
#define LFT_H

#include <functional>
#include <map>
#include <string>
#include <vector>

using cont = const std::vector<double> &;
using func1 = const std::function<bool(cont)>;
using func2 = const std::function<double(cont)>;

std::map<std::string, func1> get_primary_strategies();
std::map<std::string, func2> get_secondary_strategies();

void lft_unit_test();

#endif
