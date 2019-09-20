#ifndef REPORT_H
#define REPORT_H

#include "backtest.h"
#include "trade.h"
#include <string>
#include <vector>

std::string get_report(const std::vector<trade_t> &,
                       const std::vector<backtest_t> &, const unsigned int &,
                       const bool &);

#endif
