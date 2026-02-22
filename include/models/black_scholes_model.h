//Black scholes model header file
#pragma once

#include "option_model.h"

namespace pricing_engine::models {
  class BlackScholesModel : public OptionModel {
    double normal_cdf(double d) const;
    double calculate_d1(double underlying_price, double strike, double time_to_expiration, double volatility, double risk_free_rate) const;
    double calculate_d2(double d1, double volatility, double time_to_expiration) const;

  public:
    double price(const pricing_engine::instruments::Option& option, const pricing_engine::market_data::MarketData& market_data) const override;
  };
}