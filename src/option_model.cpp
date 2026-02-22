#include "../include/models/option_model.h"

#include <limits>
#include <cmath>
#include <algorithm>

double pricing_engine::models::OptionModel::delta(const instruments::Option& option, const market_data::MarketData& market_data) const {
  double spot = market_data.get_spot_price();
  double bump = std::max(1e-6, spot * 1e-5);

  market_data::MarketData upward_market_data = market_data;
  market_data::MarketData downward_market_data = market_data;

  upward_market_data.set_spot_price(spot + bump);
  downward_market_data.set_spot_price(spot - bump);
  
  const double upward_price = price(option, upward_market_data);
  const double downward_price = price(option, downward_market_data);
  
  return (upward_price - downward_price) / (2.0 * bump);
}

double pricing_engine::models::OptionModel::gamma(const instruments::Option& option, const market_data::MarketData& market_data) const {
  double spot = market_data.get_spot_price();
  double bump = std::max(1e-6, spot * 1e-5);

  market_data::MarketData upward_market_data = market_data;
  market_data::MarketData downward_market_data = market_data;

  upward_market_data.set_spot_price(spot + bump);
  downward_market_data.set_spot_price(spot - bump);
  
  const double upward_price = price(option, upward_market_data);
  const double downward_price = price(option, downward_market_data);
  const double base_price = price(option, market_data);
  
  return (upward_price - 2.0 * base_price + downward_price) / (bump * bump);
}

double pricing_engine::models::OptionModel::vega(const instruments::Option& option, const market_data::MarketData& market_data) const {
  double volatility = market_data.get_volatility();
  double bump = std::max(1e-4, volatility * 1e-4);

  market_data::MarketData upward_market_data = market_data;
  market_data::MarketData downward_market_data = market_data;

  upward_market_data.set_volatility(volatility + bump);
  downward_market_data.set_volatility(volatility - bump);
  
  const double upward_price = price(option, upward_market_data);
  const double downward_price = price(option, downward_market_data);
  
  return (upward_price - downward_price) / (2.0 * bump);
}

double pricing_engine::models::OptionModel::theta(const instruments::Option& option, const market_data::MarketData& market_data) const {
  double time_to_expiration = option.get_time_to_expiration();
  double bump = std::min(1.0 / 365.0, time_to_expiration);

  instruments::Option upward_option = option;
  instruments::Option downward_option = option;

  upward_option.set_time_to_expiration(time_to_expiration + bump);
  downward_option.set_time_to_expiration(time_to_expiration - bump);
  
  const double upward_price = price(upward_option, market_data);
  const double downward_price = price(downward_option, market_data);
  
  return -(upward_price - downward_price) / (2.0 * bump);
}

double pricing_engine::models::OptionModel::rho(const instruments::Option& option, const market_data::MarketData& market_data) const {
  double interest_rate = market_data.get_interest_rate();
  double bump = 1e-4;

  market_data::MarketData upward_market_data = market_data;
  market_data::MarketData downward_market_data = market_data;

  upward_market_data.set_interest_rate(interest_rate + bump);
  downward_market_data.set_interest_rate(interest_rate - bump);
  
  const double upward_price = price(option, upward_market_data);
  const double downward_price = price(option, downward_market_data);
  
  return (upward_price - downward_price) / (2.0 * bump);
}