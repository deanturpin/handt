#ifndef DETAILED_REPORT_H
#define DETAILED_REPORT_H

#include "backtest.h"
#include "trade.h"
#include <string>
#include <vector>

void get_detailed_report(const std::vector<trade_t> &,
                         const std::vector<backtest_t> &);

#endif
