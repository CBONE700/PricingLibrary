#pragma once

#include "../instruments/option.h"
#include "../market/market_data.h"

namespace pricing_engine::models {
  class OptionModel {
  public:
    virtual double compute_price(const instruments::Option& option, const market_data::MarketData& market_data) const = 0;

    virtual double compute_delta(const instruments::Option& option, const market_data::MarketData& market_data) const;
    virtual double compute_gamma(const instruments::Option& option, const market_data::MarketData& market_data) const;
    virtual double compute_vega(const instruments::Option& option, const market_data::MarketData& market_data) const;
    virtual double compute_theta(const instruments::Option& option, const market_data::MarketData& market_data) const;
    virtual double compute_rho(const instruments::Option& option, const market_data::MarketData& market_data) const;
    virtual ~OptionModel() = default;
};
}