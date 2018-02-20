#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "position.h"

int main() {

  std::vector<trade_position> positions;

  // Get closed positions
  {
    std::ifstream in("sells.csv");
    if (in.good()) {
      trade_position p;
      while (in >> p)
        positions.push_back(p);
    }
  }

  std::cout << positions.size() << " positions\n";

  // Get open positions
  {
    std::ifstream in("buys.csv");
    if (in.good()) {
      trade_position p;
      while (in >> p)
        positions.push_back(p);
    }
  }

  std::cout << positions.size() << " positions\n";
}
