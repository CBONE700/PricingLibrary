#pragma once

namespace pricing_engine::market_data {
  class MarketData {
    double spot_price;
    double interest_rate;
    double volatility;

  public:
    MarketData(double spot_price, double interest_rate, double volatility);
    
    double get_spot_price() const { return spot_price; }
    double get_interest_rate() const { return interest_rate; }
    double get_volatility() const { return volatility; }
  };
}