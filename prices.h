#ifndef PRICES_H
#define PRICES_H

#include <string>
#include <tuple>
#include <vector>

using prices_t = std::vector<
    std::tuple<std::string, std::string, std::string, std::vector<double>>>;

prices_t get_prices(const std::string &directory = "tmp");

#endif
