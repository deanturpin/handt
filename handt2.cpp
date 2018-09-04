#include <fstream>
#include <iostream>
#include <vector>

int main() {

  std::ifstream in("pairs.csv");

  struct currency_pair {
    std::string from_sym{};
    std::string to_sym{};
    std::string exchange{};
  } p;

  std::vector<currency_pair> pairs;

  while (in >> p.from_sym >> p.to_sym >> p.exchange)
    pairs.emplace_back(p);

  std::cout << pairs.size() << " pairs read\n";
}
