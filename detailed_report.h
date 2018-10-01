#ifndef DETAILED_REPORT_H
#define DETAILED_REPORT_H

#include "backtest.h"
#include "prices.h"
#include <list>
#include <string>

std::string get_detailed_report(const prices_t &,
                                const std::list<backtest_t> &);

#endif
