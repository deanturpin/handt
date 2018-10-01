#ifndef DETAILED_REPORT_H
#define DETAILED_REPORT_H

#include "backtest.h"
#include "prices.h"
#include <string>
#include <vector>

std::string get_detailed_report(const prices_t &,
                                const std::vector<backtest_t> &);

#endif
