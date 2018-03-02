#ifndef LFT_POSITION
#define LFT_POSITION

#include <iomanip>
#include <istream>
#include <ostream>
#include <chrono>
#include <string>

namespace lft {

double seconds_since_epoch() {

  using namespace std::chrono;
  using clock = std::chrono::system_clock;
  const auto now = clock::now();
  const auto epoch = static_cast<unsigned long>(
      duration_cast<seconds>(now.time_since_epoch()).count());

  return epoch;
}

// A stucture to represent a trade
struct position {

  std::string name = "name";
  unsigned long timestamp = seconds_since_epoch();
  double buy_price = 0.0;
  double sell_price = 0.0;
  std::string strategy = "strategy";
  std::string notes = "NEWTRADE";
  bool open = true;

  // Streaming out
  friend std::ostream &operator<<(std::ostream &os, const position &p) {
    os.precision(10);
    return os << std::fixed << p.name << "\t"
              << p.strategy << "\t" << p.notes << " " << p.buy_price << " "
              << p.sell_price << " " << p.timestamp << " " 
              << std::boolalpha << p.open;
  }

  // Streaming in
  friend std::istream &operator>>(std::istream &is, position &p) {
    return is >> p.name >> p.strategy >> p.notes >> p.buy_price >>
           p.sell_price >> p.timestamp >> std::boolalpha >>
           p.open;
  }
};

}

#endif
