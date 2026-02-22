#include "../instruments/option.h"
#include "../market/market_data.h"

namespace pricing_engine::models {
  class OptionModel {
  public:
    virtual double price(const instruments::Option& option, const market_data::MarketData& market_data) const = 0;

    virtual double delta(const instruments::Option& option, const market_data::MarketData& market_data) const;
    virtual double gamma(const instruments::Option& option, const market_data::MarketData& market_data) const;
    virtual double vega(const instruments::Option& option, const market_data::MarketData& market_data) const;
    virtual double theta(const instruments::Option& option, const market_data::MarketData& market_data) const;
    virtual double rho(const instruments::Option& option, const market_data::MarketData& market_data) const;

    virtual ~OptionModel() = default;
};
}