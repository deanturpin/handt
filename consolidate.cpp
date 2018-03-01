#include "position.h"
#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <fstream>

int main() {

  std::stringstream out;
  out.precision(10);
  out << std::boolalpha;

  out << "get review\n";

  // std::ifstream in("review.csv");

  // if (in.good()) {
  //   out << "review good\n";

  //   std::string line;
  //   if (in >> line)
  //     out << line;
  //   else
  //     out << "no line";
  // }

  std::ifstream in("prospects.csv");

  if (in.good()) {
    out << "review good\n";

    std::string line;
    while (getline(in, line)) {

      // Get the header
      std::stringstream ss(line);
      std::string symbol;
      double spot;
      ss >> symbol >> spot;

      // Get the matching strategies
      std::vector<std::string> strategies;
      copy(std::istream_iterator<std::string>(ss),
           std::istream_iterator<std::string>(),
                                  std::back_inserter(strategies));

      out << symbol << " " << spot << " "
        << strategies.size () << " strategies\n";
    }
  }

  // Create postion for each propsect


  // Get current positions (not necessarily for all prices)
  // const auto positions = get_positions("refresh.csv");

  // out << positions.size() << " reviewed positions\n";

  // Close any positions
  // for (auto p : positions)
  //   if (p.sell_price / p.buy_price > 1.1)
  //     p.open = false;

  // for (const auto p : positions)
  //   out << p;

  std::cout << out.str();
}
