#include "../include/market/market_data.h"
#include <stdexcept>

pricing_engine::market_data::MarketData::MarketData(double spot_price, double interest_rate, double volatility) {
    if (spot_price < 0)
      throw std::invalid_argument("Spot price must be positive.");
    if (interest_rate < 0)
      throw std::invalid_argument("Interest rate cannot be negative.");
    if (volatility < 0)
      throw std::invalid_argument("Volatility cannot be negative.");

    this->spot_price = spot_price;
    this->interest_rate = interest_rate;
    this->volatility = volatility;
  }