#pragma once

#include "../instruments/swap.h"
#include "../market/market_data.h"

namespace pricing_engine::models {
  class SwapModel {
  public:
    double compute_price(const instruments::Swap& swap, const market_data::MarketData& market_data);
  };
}