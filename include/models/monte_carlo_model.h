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

    double price(const pricing_engine::instruments::Option& option, const market_data::MarketData& market_data) const override;
    int get_steps() const { return steps; }
    int get_paths() const { return paths; }
    void set_steps(int new_steps) { steps = new_steps; }
    void set_paths(int new_paths) { paths = new_paths; }
  };
}