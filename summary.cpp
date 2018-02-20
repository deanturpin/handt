#include <fstream>
#include <iostream>
#include <string>

int main() {

  std::string line;

  // Get closed positions
  {
    unsigned long line_count = 0;
    std::ifstream sells("sells.csv");
    if (sells.good())
      while (getline(sells, line))
        ++line_count;
    std::cout << line_count << " sells\n";
  }

  // Get open positions
  {
    unsigned long line_count = 0;
    std::ifstream buys("buys.csv");
    if (buys.good())
      while (getline(buys, line))
        ++line_count;
    std::cout << line_count << " buys\n";
  }
}
