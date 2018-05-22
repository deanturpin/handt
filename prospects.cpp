#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "include/handt.h"
#include "include/strategy.h"

int main() {
  // Test strategies on each series
  for (const auto &p : handt::get_prices())
    if (!p.series.empty()) {
      const unsigned long frame_size = 120;

      // Chop the whole series up into chunks
      for (auto i = p.series.cbegin();
           i != std::prev(p.series.cend(), frame_size); ++i) {

        decltype(p.series) frame;
        std::copy(i, std::next(i, frame_size), std::back_inserter(frame));

        const auto &buys = strategy::library(frame);

        if (!buys.empty()) {

          std::cout << p.from_symbol << '-' << p.to_symbol << '\n';
          std::cout << buys.size() << " strategies triggered\n";

          const auto spot = frame.back();
          std::cout << spot << ' ';
          const auto target_price = handt::sell_threshold * spot;

          // Spin forward to see if there's a sell in the future
          if (std::find_if(i, p.series.cend(),
                           [&target_price](const auto &price) {

                             return price == target_price;
                           }) != p.series.end())
            std::cout << target_price << " - profit\n";
          else
            std::cout << target_price << " - no profit\n";

          // for (const auto &buy : buys)
          //   std::cout << buy << ' ';
          // std::cout << '\n';
        }

        break;
      }
    }
}
