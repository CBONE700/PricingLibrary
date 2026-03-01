#pragma once

#include "../instruments/swap.h"

namespace pricing_engine::models {
  class SwapModel {
  public:
    double compute_price(const pricing_engine::instruments::Swap& swap);
  };
}