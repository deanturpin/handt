#ifndef REPORT_H
#define REPORT_H

#include "handt.h"
#include "prices.h"
#include <list>
#include <sstream>
#include <string>

static_assert(std::is_standard_layout<strategy_performance>::value);
std::string report_performance(const prices_t &,
                               const std::list<strategy_performance> &);

#endif
