#pragma once

#include "../instruments/futures.h"
#include "../market/market_data.h"

namespace pricing_engine::models {
  class FuturesModel {
  public:
    double compute_price(const instruments::Future& future, const market_data::MarketData& market_data);
  };
}