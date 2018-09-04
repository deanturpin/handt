#include <fstream>
#include <iostream>
#include <vector>

// A currency pair is a duo of symbols and an exchange whence the price came
struct currency_pair {
  std::string from_sym{};
  std::string to_sym{};
  std::string exchange{};
};

std::vector<currency_pair> get_pairs() {

  currency_pair p;

  // Extract and store the portfolio of currency pairs
  std::vector<currency_pair> pairs;
  std::ifstream in("pairs.csv");
  while (in >> p.from_sym >> p.to_sym >> p.exchange)
    pairs.emplace_back(p);

  return pairs;
}

int main() {

  // Fetch the pairs we're interested in
  const auto &pairs = get_pairs();
  std::cout << pairs.size() << " pairs read\n";

  // Form a price request
  for (const auto &request : get_pairs())
    std::cout << request.from_sym << '\t' << request.to_sym << '\t'
              << request.exchange << '\n';
}
