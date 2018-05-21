#include "include/handt.h"
#include "include/strategy.h"
#include <iostream>
#include <vector>

int main() {

  // Test strategies on each series
  for (const auto &p : handt::get_prices())
    if (!p.series.empty())
    {

      const unsigned long frame_size = 120;

      // Chop the whole series up into chunks
      for (auto i = p.series.cbegin(); i != std::prev(p.series.cend(), frame_size); ++i) 
      {

        decltype(p.series) frame;

        std::copy(i, std::next(i, frame_size), std::back_inserter(frame));

        const auto &buys = strategy::library(frame);

        // If some strategies have triggered then print them
        if (!buys.empty()) {
          const auto spot = frame.back();
          std::cout << p.from_symbol << '\t' << p.to_symbol << '\t' << spot
                    << ' ';
          for (const auto &buy : buys)
            std::cout << buy << ' ';
          std::cout << '\n';
        }
      }
    }
}
