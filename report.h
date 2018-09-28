#ifndef REPORT_H
#define REPORT_H

#include "handt.h"
#include "prices.h"
#include <list>
#include <sstream>
#include <string>

static_assert(std::is_standard_layout<backtest_t>::value);
std::string report_performance(const prices_t &, const std::list<backtest_t> &);

#endif
