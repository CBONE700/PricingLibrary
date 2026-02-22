#pragma once

#include "../instruments/futures.h"
#include "../market/market_data.h"

namespace pricing_engine::models {
  class FuturesModel {
  public:
    double price(const pricing_engine::instruments::Future& future, const pricing_engine::market_data::MarketData& market_data);
  };
}