#include "handt.h"
#include "perms.h"
#include "prices.h"
#include "report.h"
#include "unit_test.h"

int main() {

  unit_test();

  // Get the latest prices
  const auto &prices = get_prices();

  // Get the strategies
  const auto &perms = get_strategies();

  // Run backtests
  const auto &backtests = have_a_nice_day_trader(prices, perms);

  // Generate report
  const auto &report = get_report(prices, backtests);

  // Print report
  std::puts(report.c_str());
}
