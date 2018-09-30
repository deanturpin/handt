#ifndef REPORT_H
#define REPORT_H

#include "backtest.h"
#include "prices.h"
#include <list>
#include <sstream>
#include <string>

static_assert(std::is_standard_layout<backtest_t>::value);
std::string get_report(const prices_t &, const std::list<backtest_t> &);
std::string get_detailed_report(const prices_t &,
                                const std::list<backtest_t> &);

#endif
