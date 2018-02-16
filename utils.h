#ifndef UTILS
#define UTILS

#include <map>
#include <chrono>
#include <sstream>
#include <iterator>
#include <fstream>
#include <iomanip>

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

      // Extract values into a container
      std::vector<double> p;
      copy(std::istream_iterator<double>(ss), std::istream_iterator<double>(),
           std::back_inserter(p));

      prices.insert(std::make_pair(coin, p));
    }
  }

  return prices;
}

// Turn right now into a string timestamp
std::string timestamp() {

  // Get now
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
