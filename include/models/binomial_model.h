#pragma once

#include "option_model.h"

namespace pricing_engine::models {
  class BinomialModel : public OptionModel {
    int steps;
  public:
    explicit BinomialModel(int steps);

    double compute_price(const pricing_engine::instruments::Option& option, const market_data::MarketData& market_data) const override;
  };
}