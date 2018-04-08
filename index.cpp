#include "handt.h"
#include "html.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

int main() {

  // Configure debug
  std::stringstream out;
  out.precision(2);
  out << std::fixed;

  // Get some data to play with
  auto positions = handt::get_final_positions();
  auto closed = handt::get_closed_positions();
  const auto &prices = handt::get_prices();
  const auto &symbols = handt::get_symbols().size();
  const auto &balance = handt::get_balance();
  const auto open_positions = positions.size();
  const unsigned long batch_size = 80UL;

  // Print the bulk of the HTML
  out << R"(
<!DOCTYPE html>

<meta charset="UTF-8">
<meta name="robots" content="index,follow" />
<meta http-equiv="refresh" content="30" />
<link rel=icon href="favicon.ico" sizes="any">

<style>
body { font-family: sans-serif; }
pre#floater { float: right; }
</style>

<title>HANDT</title>
<h1>HAVE A NICE DAY TRADER</h1>

<p id="disclaimer">History is no indicator of future performance. Don't invest
what you can't afford to lose. Prices fetched periodically from <a
href="https://www.cryptocompare.com/api/" target="blah">CryptoCompare</a>. See
the documentation on <a href="https://deanturpin.github.io/handt"
target="blah">GitHub</a>.</p>)"
      << "\n\n<p>24 hours of prices are fetched for " << symbols
      << " coins at a rate of " << batch_size
      << " per minute&mdash;a limit set by the exchange&mdash;therefore it "
         "takes "
      << symbols / batch_size
      << " minutes to process the full set of coins. A library of strategies "
         "is run over each batch and a position is created if the strategy "
         "returns positively. Positions are closed if either the sell price "
         "exceeds "
      << handt::sell_threshold * 100.0
      << "&nbsp;% of the buy price or 24 hours have elapsed since creation. A "
         "position can also be closed if the return falls below "
      << handt::cut_losses_threshold * 100.0
      << "&nbsp;%. The total return and exposure are updated as each position "
         "is "
         "created (or closed) and all trades are $"
      << handt::trade_size
      << ". This trade size was chosen as it's large enough to ignore the "
         "fees on a Coinbase trade.</p>\n\n";

  // Close all positions and split into cap size
  std::map<std::string, std::vector<double>> strategy_summary;
  for (const auto &position : closed)
    strategy_summary[position.strategy].push_back(position.yield());

  // Print summary of open positions, sorted by yield
  std::sort(positions.begin(), positions.end(),
            [](const auto &a, const auto &b) { return a.yield() > b.yield(); });
  out << "<pre id='floater'>\n";
  out << "Open positions\n";
  for (const auto &position : positions)
    out << position.symbol << '\t' << position.yield() * 100.0 << '\t'
        << position.strategy << '\t' << position.buy_price << '\n';
  out << "</pre>\n";

  // Calculate the value of the currrent exposure if we were to cash out now
  const double exposure = open_positions * handt::trade_size;
  const double exposure_value =
      handt::trade_size * std::accumulate(positions.cbegin(), positions.cend(),
                                          0.0,
                                          [](auto &sum, const auto &position) {
                                            return sum + position.yield();
                                          });

  // Pretty print
  const auto plural = prices.size() == 1 ? "" : "s";

  // Print trade summary
  out << "<h3>Return: $" << balance;
  out << "<br>Exposure: $" << exposure << " ($" << exposure_value - exposure
      << " cash out)</h3>\n";
  out << "<p>";
  out << prices.size() << " coin" << plural << " updated in the last minute.";
  out << "</p>\n";

  // Print strategy summary
  out << "<pre>\n";
  out << "STRATEGY\t\t POS\t% RETURN\n";
  for (const auto &i : strategy_summary) {
    const unsigned long positions_held = i.second.size();
    const double yield =
        100.0 * std::accumulate(i.second.cbegin(), i.second.cend(), 0.0) /
        positions_held;

    out << i.first << "\t" << positions_held << "\t" << yield << "\n";
  }
  out << "</pre>\n";

  // Closed positions
  out << "<h2>Closed positions</h2>\n";
  out << "<pre>\n";
  std::sort(closed.begin(), closed.end(), [](const auto &a, const auto &b) {
    return a.strategy < b.strategy;
  });

  for (const auto &p : closed)
    out << p.symbol << '\t' << 100.0 * p.yield() << '\t' << p.strategy << '\t'
        << p.status << '\n';
  out << "</pre>\n";

  std::cout << out.str();
}
