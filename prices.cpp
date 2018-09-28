#include "prices.h"
#include <filesystem>
#include <fstream>
#include <iterator>
#include <tuple>
#include <vector>

// Take a directory name, read all the files and return a container of prices
// for all coins

prices_t get_prices(const std::string &directory) {

  prices_t prices;

  // Fetch list of price files
  std::vector<std::string> currency_pairs;
  for (const auto &file : std::filesystem::directory_iterator(directory))
    currency_pairs.emplace_back(file.path());

  // Extract prices from each file
  for (const auto &file : currency_pairs) {

    // Open prices and get the trade info
    std::ifstream in(file);
    std::string from_symbol, to_symbol, exchange;
    in >> from_symbol >> to_symbol >> exchange;

    // Get the prices and run the strategies over them
    const std::vector<double> latest{std::istream_iterator<double>(in), {}};

    // Only store prices if the parse was successful
    if (!latest.empty())
      prices.push_back({from_symbol, to_symbol, exchange, latest});
  }

  return prices;
}
