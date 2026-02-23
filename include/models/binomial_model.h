#pragma once

#include "option_model.h"

namespace pricing_engine::models {
  class BinomialModel : public OptionModel {
    int steps;
  public:
    explicit BinomialModel(int steps);

    double price(const pricing_engine::instruments::Option& option, const market_data::MarketData& market_data) const override;
    int get_steps() const { return steps; }
    void set_steps(int new_steps) { steps = new_steps; }
  };
}