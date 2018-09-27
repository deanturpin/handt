#ifndef PRICES_H
#define PRICES_H

#include <string>
#include <tuple>
#include <vector>

using return_type = std::vector<
    std::tuple<std::string, std::string, std::string, std::vector<double>>>;

return_type get_prices(const std::string directory = "tmp");

#endif
