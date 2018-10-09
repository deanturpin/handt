#include "trade.h"
#include <filesystem>
#include <fstream>
#include <iterator>
#include <vector>

// Take a directory name, read all the files and return a container of prices
// for all coins

std::vector<trade_t> get_trades() {

  std::vector<trade_t> trades;

  // Fetch list of price files
  std::vector<std::string> currency_pairs;
  for (const auto &file : std::filesystem::directory_iterator("tmp"))
    if (std::string(file.path()).find(".csv") != std::string::npos)
      currency_pairs.emplace_back(file.path());

  // Extract prices from each file
  for (const auto &file : currency_pairs) {

    // Open prices and get the trade info
    std::ifstream in(file);
    std::string from_symbol, to_symbol, exchange;
    in >> from_symbol >> to_symbol >> exchange;

    // Get the latest prices and run the strategies over them
    const std::vector<double> prices{std::istream_iterator<double>(in), {}};

    // Only store prices if the parse was successful
    if (!prices.empty())
      trades.push_back({from_symbol, to_symbol, exchange, prices});
  }

  return trades;
}
