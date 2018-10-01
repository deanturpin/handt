#ifndef REPORT_H
#define REPORT_H

#include "backtest.h"
#include "prices.h"
#include <string>
#include <vector>

static_assert(std::is_standard_layout<backtest_t>::value);
std::string get_report(const std::vector<trade_t> &,
                       const std::vector<backtest_t> &);

#endif
