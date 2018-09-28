#include "handt.h"
#include "prices.h"
#include "report.h"
#include "strategy.h"
#include "unit_test.h"

int main() {

  unit_test();

  // Fetch the latest prices and have a nice day (trader)
  const auto &prices = get_prices();
  const auto &performance = have_a_nice_day_trader(prices);
  report_performance(performance);
}
