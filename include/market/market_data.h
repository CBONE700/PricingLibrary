#pragma once

namespace pricing_engine::market_data {
  struct MarketData {
    double spot_price;
    double rate;
    double volatility;
  };
}