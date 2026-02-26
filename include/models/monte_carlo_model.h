#pragma once

#include "option_model.h"
#include <random>

namespace pricing_engine::models {
  class MonteCarloModel : public OptionModel {
    int steps;
    int paths;
    std::mt19937 rng;

  public:
    MonteCarloModel(int steps, int paths);

    double compute_price(const pricing_engine::instruments::Option& option, const market_data::MarketData& market_data) const override;
  };
}