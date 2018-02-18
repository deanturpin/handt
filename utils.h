#ifndef UTILS
#define UTILS

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <map>
#include <sstream>
#include <vector>

// Prototypes
std::map<std::string, std::vector<double>> get_prices();
std::string timestamp();

// Get prices and return a container full of them
std::map<std::string, std::vector<double>> get_prices() {
  std::map<std::string, std::vector<double>> prices;

  // Read some prices
  std::ifstream in("prices.csv");
  if (in.good()) {

    // The first item is the coin name
    std::string coin;
    while (in >> coin) {

      // The remainder of the line contains values
      std::string line;
      std::getline(in, line);
      std::stringstream ss(line);

      // Extract values and add to the map
      std::vector<double> p;
      copy(std::istream_iterator<double>(ss), std::istream_iterator<double>(),
           std::back_inserter(p));

      prices.insert(std::make_pair(coin, p));
    }
  }

  return prices;
}

// Get the time right now and turn it into a human-readable string
std::string timestamp() {

  // Get time now
  using namespace std::chrono;
  using clock = std::chrono::system_clock;
  const auto now = clock::now();

  // Create a date string
  const auto in_time_t = clock::to_time_t(now);
  std::stringstream date;
  date << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d-%X");

  return date.str();
}

#endif
