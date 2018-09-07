#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

int main() {

  // A currency pair is a duo of symbols and an exchange whence the price came
  struct currency_pair {
    std::string from_sym{};
    std::string to_sym{};
    std::string exchange{};
  };

  const std::vector<currency_pair> pairs{
      {"SALT", "ETH", "Binance"},      {"SALT", "BTC", "Binance"},
      {"XMR", "ETH", "Binance"},       {"XMR", "BTC", "Binance"},
      {"IOT", "BNB", "Binance"},       {"IOT", "BTC", "Binance"},
      {"IOT", "ETH", "Binance"},       {"EOS", "BTC", "Binance"},
      {"EOS", "ETH", "Binance"},       {"ETH", "USDT", "Binance"},
      {"ETH", "BTC", "Binance"},       {"XVG", "ETH", "Binance"},
      {"XVG", "BTC", "Binance"},       {"AMB", "BTC", "Binance"},
      {"AMB", "ETH", "Binance"},       {"AMB", "BNB", "Binance"},
      {"HSR", "BTC", "Binance"},       {"HSR", "ETH", "Binance"},
      {"BTC", "USDT", "Binance"},      {"POE", "BTC", "Binance"},
      {"POE", "ETH", "Binance"},       {"KMD", "BTC", "Binance"},
      {"KMD", "ETH", "Binance"},       {"REQ", "ETH", "Binance"},
      {"REQ", "BTC", "Binance"},       {"BTS", "ETH", "Binance"},
      {"BTS", "BTC", "Binance"},       {"BTS", "BNB", "Binance"},
      {"BCD", "ETH", "Binance"},       {"BCD", "BTC", "Binance"},
      {"ZRX", "ETH", "Binance"},       {"ZRX", "BTC", "Binance"},
      {"XRP", "BTC", "Binance"},       {"XRP", "ETH", "Binance"},
      {"LINK", "BTC", "Binance"},      {"LINK", "ETH", "Binance"},
      {"TNT", "ETH", "Binance"},       {"TNT", "BTC", "Binance"},
      {"XRB", "ETH", "Binance"},       {"XRB", "BNB", "Binance"},
      {"XRB", "BTC", "Binance"},       {"EVX", "ETH", "Binance"},
      {"EVX", "BTC", "Binance"},       {"BQX", "ETH", "Binance"},
      {"BQX", "BTC", "Binance"},       {"CDT", "ETH", "Binance"},
      {"CDT", "BTC", "Binance"},       {"FUN", "ETH", "Binance"},
      {"FUN", "BTC", "Binance"},       {"NULS", "BTC", "Binance"},
      {"NULS", "BNB", "Binance"},      {"NULS", "ETH", "Binance"},
      {"ETC", "ETH", "Binance"},       {"ETC", "BTC", "Binance"},
      {"DNT", "ETH", "Binance"},       {"DNT", "BTC", "Binance"},
      {"GRS", "BTC", "Binance"},       {"GRS", "ETH", "Binance"},
      {"SNGLS", "ETH", "Binance"},     {"SNGLS", "BTC", "Binance"},
      {"APPC", "BNB", "Binance"},      {"APPC", "ETH", "Binance"},
      {"APPC", "BTC", "Binance"},      {"XLM", "BTC", "Binance"},
      {"XLM", "BNB", "Binance"},       {"XLM", "ETH", "Binance"},
      {"MOD", "ETH", "Binance"},       {"MOD", "BTC", "Binance"},
      {"RLC", "BNB", "Binance"},       {"RLC", "BTC", "Binance"},
      {"RLC", "ETH", "Binance"},       {"OMG", "ETH", "Binance"},
      {"OMG", "BTC", "Binance"},       {"WAN", "ETH", "Binance"},
      {"WAN", "BNB", "Binance"},       {"WAN", "BTC", "Binance"},
      {"LSK", "ETH", "Binance"},       {"LSK", "BNB", "Binance"},
      {"LSK", "BTC", "Binance"},       {"CHAT", "ETH", "Binance"},
      {"CHAT", "BTC", "Binance"},      {"PIVX", "BNB", "Binance"},
      {"PIVX", "ETH", "Binance"},      {"PIVX", "BTC", "Binance"},
      {"WPR", "ETH", "Binance"},       {"WPR", "BTC", "Binance"},
      {"WABI", "BTC", "Binance"},      {"WABI", "ETH", "Binance"},
      {"WABI", "BNB", "Binance"},      {"LRC", "BTC", "Binance"},
      {"LRC", "ETH", "Binance"},       {"BCPT", "ETH", "Binance"},
      {"BCPT", "BNB", "Binance"},      {"BCPT", "BTC", "Binance"},
      {"NEBL", "ETH", "Binance"},      {"NEBL", "BTC", "Binance"},
      {"NEBL", "BNB", "Binance"},      {"DGD", "ETH", "Binance"},
      {"DGD", "BTC", "Binance"},       {"BCN", "BNB", "Binance"},
      {"BCN", "BTC", "Binance"},       {"BCN", "ETH", "Binance"},
      {"VEN", "ETH", "Binance"},       {"VEN", "BTC", "Binance"},
      {"VEN", "BNB", "Binance"},       {"LTC", "USDT", "Binance"},
      {"LTC", "ETH", "Binance"},       {"LTC", "BTC", "Binance"},
      {"LTC", "BNB", "Binance"},       {"ONT", "BNB", "Binance"},
      {"ONT", "ETH", "Binance"},       {"ONT", "BTC", "Binance"},
      {"STORJ", "ETH", "Binance"},     {"STORJ", "BTC", "Binance"},
      {"DLT", "ETH", "Binance"},       {"DLT", "BNB", "Binance"},
      {"DLT", "BTC", "Binance"},       {"WTC", "BNB", "Binance"},
      {"WTC", "ETH", "Binance"},       {"WTC", "BTC", "Binance"},
      {"AE", "BNB", "Binance"},        {"AE", "ETH", "Binance"},
      {"AE", "BTC", "Binance"},        {"MANA", "ETH", "Binance"},
      {"MANA", "BTC", "Binance"},      {"BTG", "BTC", "Binance"},
      {"BTG", "ETH", "Binance"},       {"ARK", "BTC", "Binance"},
      {"ARK", "ETH", "Binance"},       {"STEEM", "BNB", "Binance"},
      {"STEEM", "ETH", "Binance"},     {"STEEM", "BTC", "Binance"},
      {"INS", "ETH", "Binance"},       {"INS", "BTC", "Binance"},
      {"VIB", "BTC", "Binance"},       {"VIB", "ETH", "Binance"},
      {"OST", "BTC", "Binance"},       {"OST", "ETH", "Binance"},
      {"OST", "BNB", "Binance"},       {"CMT*", "BTC", "Binance"},
      {"CMT*", "BNB", "Binance"},      {"CMT*", "ETH", "Binance"},
      {"NCASH", "BNB", "Binance"},     {"NCASH", "BTC", "Binance"},
      {"NCASH", "ETH", "Binance"},     {"OAX", "BTC", "Binance"},
      {"OAX", "ETH", "Binance"},       {"LLT", "BTC", "Binance"},
      {"WINGS", "BTC", "Binance"},     {"WINGS", "ETH", "Binance"},
      {"GTO", "ETH", "Binance"},       {"GTO", "BTC", "Binance"},
      {"GTO", "BNB", "Binance"},       {"RDN*", "BTC", "Binance"},
      {"RDN*", "ETH", "Binance"},      {"RDN*", "BNB", "Binance"},
      {"SUB", "BTC", "Binance"},       {"SUB", "ETH", "Binance"},
      {"RCN", "BTC", "Binance"},       {"RCN", "BNB", "Binance"},
      {"RCN", "ETH", "Binance"},       {"STORM", "BNB", "Binance"},
      {"STORM", "ETH", "Binance"},     {"STORM", "BTC", "Binance"},
      {"BTM", "ETH", "Binance"},       {"STRAT", "ETH", "Binance"},
      {"STRAT", "BTC", "Binance"},     {"ZIL", "BTC", "Binance"},
      {"ZIL", "BNB", "Binance"},       {"ZIL", "ETH", "Binance"},
      {"POA", "ETH", "Binance"},       {"POA", "BNB", "Binance"},
      {"POA", "BTC", "Binance"},       {"XZC", "BTC", "Binance"},
      {"XZC", "ETH", "Binance"},       {"XZC", "BNB", "Binance"},
      {"MCO", "BTC", "Binance"},       {"MCO", "BNB", "Binance"},
      {"MCO", "ETH", "Binance"},       {"CTR", "ETH", "Binance"},
      {"CTR", "BTC", "Binance"},       {"BNT", "BTC", "Binance"},
      {"BNT", "ETH", "Binance"},       {"CND", "BNB", "Binance"},
      {"CND", "BTC", "Binance"},       {"CND", "ETH", "Binance"},
      {"VIA", "BTC", "Binance"},       {"VIA", "BNB", "Binance"},
      {"VIA", "ETH", "Binance"},       {"TRX", "BTC", "Binance"},
      {"TRX", "ETH", "Binance"},       {"LUN", "ETH", "Binance"},
      {"LUN", "BTC", "Binance"},       {"BNB", "USDT", "Binance"},
      {"BNB", "BTC", "Binance"},       {"BNB", "ETH", "Binance"},
      {"ICN", "BTC", "Binance"},       {"ICN", "ETH", "Binance"},
      {"LEND", "ETH", "Binance"},      {"LEND", "BTC", "Binance"},
      {"KNC", "ETH", "Binance"},       {"KNC", "BTC", "Binance"},
      {"SNM", "ETH", "Binance"},       {"SNM", "BTC", "Binance"},
      {"ARN", "ETH", "Binance"},       {"ARN", "BTC", "Binance"},
      {"ZEC", "ETH", "Binance"},       {"ZEC", "BTC", "Binance"},
      {"FUEL", "BTC", "Binance"},      {"FUEL", "ETH", "Binance"},
      {"MTL", "ETH", "Binance"},       {"MTL", "BTC", "Binance"},
      {"GVT", "ETH", "Binance"},       {"GVT", "BTC", "Binance"},
      {"MDA", "BTC", "Binance"},       {"MDA", "ETH", "Binance"},
      {"TRIG", "BNB", "Binance"},      {"TRIG", "BTC", "Binance"},
      {"TRIG", "ETH", "Binance"},      {"POWR", "BTC", "Binance"},
      {"POWR", "BNB", "Binance"},      {"POWR", "ETH", "Binance"},
      {"BCH", "ETH", "Binance"},       {"BCH", "USDT", "Binance"},
      {"BCH", "BTC", "Binance"},       {"BCH", "BNB", "Binance"},
      {"TNB", "ETH", "Binance"},       {"TNB", "BTC", "Binance"},
      {"QTUM", "USDT", "Binance"},     {"QTUM", "BTC", "Binance"},
      {"QTUM", "ETH", "Binance"},      {"QTUM", "BNB", "Binance"},
      {"BRD", "BNB", "Binance"},       {"BRD", "ETH", "Binance"},
      {"BRD", "BTC", "Binance"},       {"YOYO", "ETH", "Binance"},
      {"SYS", "BNB", "Binance"},       {"SYS", "BTC", "Binance"},
      {"SYS", "ETH", "Binance"},       {"CLOAK", "BTC", "Binance"},
      {"CLOAK", "ETH", "Binance"},     {"ELC", "BTC", "Binance"},
      {"XEM", "ETH", "Binance"},       {"XEM", "BTC", "Binance"},
      {"XEM", "BNB", "Binance"},       {"NAV", "BNB", "Binance"},
      {"NAV", "ETH", "Binance"},       {"NAV", "BTC", "Binance"},
      {"ADA", "BTC", "Binance"},       {"ADA", "ETH", "Binance"},
      {"BLZ", "BTC", "Binance"},       {"BLZ", "ETH", "Binance"},
      {"BLZ", "BNB", "Binance"},       {"ENJ", "BTC", "Binance"},
      {"ENJ", "ETH", "Binance"},       {"HCC", "BTC", "Binance"},
      {"GAS", "BTC", "Binance"},       {"ELF", "ETH", "Binance"},
      {"ELF", "BTC", "Binance"},       {"AST", "BTC", "Binance"},
      {"AST", "ETH", "Binance"},       {"VIBE", "ETH", "Binance"},
      {"VIBE", "BTC", "Binance"},      {"IOTA", "ETH", "Binance"},
      {"IOTA", "BTC", "Binance"},      {"SNT", "ETH", "Binance"},
      {"SNT", "BTC", "Binance"},       {"PPT", "ETH", "Binance"},
      {"PPT", "BTC", "Binance"},       {"MTH", "BTC", "Binance"},
      {"MTH", "ETH", "Binance"},       {"ADX", "ETH", "Binance"},
      {"ADX", "BNB", "Binance"},       {"ADX", "BTC", "Binance"},
      {"ICX", "ETH", "Binance"},       {"ICX", "BTC", "Binance"},
      {"ICX", "BNB", "Binance"},       {"QSP", "BNB", "Binance"},
      {"QSP", "ETH", "Binance"},       {"QSP", "BTC", "Binance"},
      {"ENG", "BTC", "Binance"},       {"ENG", "ETH", "Binance"},
      {"AION", "BNB", "Binance"},      {"AION", "BTC", "Binance"},
      {"AION", "ETH", "Binance"},      {"BAT", "BNB", "Binance"},
      {"BAT", "ETH", "Binance"},       {"BAT", "BTC", "Binance"},
      {"IOST", "ETH", "Binance"},      {"IOST", "BTC", "Binance"},
      {"GNT", "ETH", "Binance"},       {"GNT", "BNB", "Binance"},
      {"GNT", "BTC", "Binance"},       {"WAVES", "BTC", "Binance"},
      {"WAVES", "ETH", "Binance"},     {"WAVES", "BNB", "Binance"},
      {"DASH", "ETH", "Binance"},      {"DASH", "BTC", "Binance"},
      {"YOYOW", "BNB", "Binance"},     {"YOYOW", "BTC", "Binance"},
      {"YOYOW", "ETH", "Binance"},     {"QLC", "BTC", "Binance"},
      {"QLC", "ETH", "Binance"},       {"QLC", "BNB", "Binance"},
      {"GXS", "BTC", "Binance"},       {"GXS", "ETH", "Binance"},
      {"EDO", "BTC", "Binance"},       {"EDO", "ETH", "Binance"},
      {"NEO", "USDT", "Binance"},      {"NEO", "ETH", "Binance"},
      {"NEO", "BNB", "Binance"},       {"NEO", "BTC", "Binance"},
      {"RPX", "ETH", "Binance"},       {"RPX", "BTC", "Binance"},
      {"RPX", "BNB", "Binance"},       {"BTC", "USD", "Coinbase"},
      {"BTC", "GBP", "Coinbase"},      {"BTC", "EUR", "Coinbase"},
      {"BTC", "CAD", "Coinbase"},      {"LTC", "BTC", "Coinbase"},
      {"LTC", "USD", "Coinbase"},      {"LTC", "EUR", "Coinbase"},
      {"BCH", "EUR", "Coinbase"},      {"BCH", "USD", "Coinbase"},
      {"BCH", "BTC", "Coinbase"},      {"ETH", "BTC", "Coinbase"},
      {"ETH", "USD", "Coinbase"},      {"ETH", "EUR", "Coinbase"},
      {"ETC", "BTC", "Coinbase"},      {"ETC", "EUR", "Coinbase"},
      {"ETC", "USD", "Coinbase"},      {"ETC", "BAD", "Coinbase"},
      {"BAD", "USD", "NotAnExchange"}, {"Not", "Enough"},
  };

  // The pairs we're interested in
  std::cout << pairs.size() << " pairs read\n";

  // for (const auto &[from_sym, to_sym, exchange] : pairs)
  // std::cout << from_sym << '\n';

  // Get prices
  for (const auto &file : std::filesystem::directory_iterator("tmp")) {

    // Get the trade params
    std::ifstream in(file.path());
    if (currency_pair p; in >> p.from_sym >> p.to_sym >> p.exchange)
      std::cout << "Processing " << p.from_sym << " from symbol\n";

    // Get the prices
    const std::vector<double> prices{std::istream_iterator<double>(in), {}};

    if (!prices.empty()) {

      std::cout << prices.size() << " prices read\n";

      // Backtest
      std::cout << std::accumulate(prices.cbegin(), prices.cend(), 0.0) /
                       prices.size()
                << " average price\n";

      // Configure trading period
      const unsigned int analysis_window = 24;
      const unsigned int sell_window     = analysis_window * 2;

      // Set up some indices into the prices
      auto earliest_price = prices.cbegin();
      auto latest_price   = std::next(earliest_price, analysis_window);
      auto future_price   = std::next(latest_price, sell_window);

      // Stat reporting
      unsigned int successes              = 0;
      unsigned int fails                  = 0;
      unsigned int opportunities_to_trade = 0;

      while (future_price < prices.cend()) {

        const double buy_threshold  = 1.2;
        const double sell_threshold = 1.01;

        // Check if we're ready to trade
        if (*earliest_price / *latest_price > buy_threshold) {

          // Find the first opportunity to sell in the future sell window
          const auto sell_price =
              std::find_if(latest_price, future_price,
                           [&latest_price, &sell_threshold](const auto &p) {
                             return p > (*latest_price * sell_threshold);
                           });

          // Look ahead to see if we would have cashed in the trade
          if (sell_price != future_price) {
            ++successes;

            // Move the trade window to the first opportunity to sell
            earliest_price = sell_price;
          }
        } else
          ++fails;

        std::advance(earliest_price, 1);

        latest_price = std::next(earliest_price, analysis_window);
        future_price = std::next(latest_price, sell_window);

        ++opportunities_to_trade;
      }

      std::cout << successes << " successes\n";
      std::cout << fails << " fails\n";
      std::cout << opportunities_to_trade << " opportunities to trade\n";

      std::cout << 100.0 * successes / fails << " % success rate\n";
    }
  }
}
