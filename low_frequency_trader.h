#ifndef LFT_H
#define LFT_H

#include <functional>
#include <string>
#include <vector>

using cont = const std::vector<double> &;
using func1 = std::function<bool(cont)>;
using func2 = std::function<double(cont)>;

std::vector<std::pair<std::string, func1>> get_primary_strategies();
std::vector<std::pair<std::string, func2>> get_secondary_strategies();

void lft_unit_test();

#endif
