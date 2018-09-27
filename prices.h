#ifndef PRICES_H
#define PRICES_H

#include <filesystem>
#include <fstream>
#include <iterator>
#include <list>
#include <tuple>

#include <string>

using return_type = std::vector<
    std::tuple<std::string, std::string, std::string, std::vector<double>>>;

return_type get_prices(const std::string directory = "tmp");

#endif
