#include "handt.h"
#include "prices.h"
#include "report.h"
#include "strategy.h"
#include "unit_test.h"

int main() {

  unit_test();

  // Fetch the latest prices
  const auto &prices = get_prices();

  // Run backtests
  const auto &backtests = have_a_nice_day_trader(prices);

  // Generate report
  const auto &report = report_performance(prices, backtests);

  std::puts(report.c_str());
}
