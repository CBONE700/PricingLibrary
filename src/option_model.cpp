#include "../include/models/option_model.h"

#include <limits>
#include <cmath>
#include <algorithm>

double pricing_engine::models::OptionModel::compute_delta(const instruments::Option& option, const market_data::MarketData& market_data) const {
  double spot = market_data.get_spot_price();
  double bump = std::max(1e-6, spot * 1e-5);

  market_data::MarketData upward_market_data = market_data::MarketData(market_data.get_spot_price() + bump, market_data.get_interest_rate(), market_data.get_volatility());
  market_data::MarketData downward_market_data = market_data::MarketData(market_data.get_spot_price() - bump, market_data.get_interest_rate(), market_data.get_volatility());
  
  const double upward_price = compute_price(option, upward_market_data);
  const double downward_price = compute_price(option, downward_market_data);
  
  return (upward_price - downward_price) / (2.0 * bump);
}

double pricing_engine::models::OptionModel::compute_gamma(const instruments::Option& option, const market_data::MarketData& market_data) const {
  double spot = market_data.get_spot_price();
  double bump = std::max(1e-3, spot * 1e-2);

  market_data::MarketData upward_market_data = market_data::MarketData(market_data.get_spot_price() + bump, market_data.get_interest_rate(), market_data.get_volatility());
  market_data::MarketData downward_market_data = market_data::MarketData(market_data.get_spot_price() - bump, market_data.get_interest_rate(), market_data.get_volatility());
  
  const double upward_price = compute_price(option, upward_market_data);
  const double downward_price = compute_price(option, downward_market_data);
  const double base_price = compute_price(option, market_data);
  
  return (upward_price - 2.0 * base_price + downward_price) / (bump * bump);
}

double pricing_engine::models::OptionModel::compute_vega(const instruments::Option& option, const market_data::MarketData& market_data) const {
  double volatility = market_data.get_volatility();
  double bump = std::max(1e-4, volatility * 1e-4);

  market_data::MarketData upward_market_data = market_data::MarketData(market_data.get_spot_price(), market_data.get_interest_rate(), volatility + bump);
  market_data::MarketData downward_market_data = market_data::MarketData(market_data.get_spot_price(), market_data.get_interest_rate(), volatility - bump);
  
  const double upward_price = compute_price(option, upward_market_data);
  const double downward_price = compute_price(option, downward_market_data);
  
  return (upward_price - downward_price) / (2.0 * bump);
}

double pricing_engine::models::OptionModel::compute_theta(const instruments::Option& option, const market_data::MarketData& market_data) const {
  double time_to_expiration = option.get_time_to_expiration();
  double bump = std::min(1.0 / 365.0, time_to_expiration);

  instruments::Option upward_option = instruments::Option(option.get_strike(), time_to_expiration + bump, option.get_type(), option.get_style());
  instruments::Option downward_option = instruments::Option(option.get_strike(), time_to_expiration - bump, option.get_type(), option.get_style());
  
  const double upward_price = compute_price(upward_option, market_data);
  const double downward_price = compute_price(downward_option, market_data);
  
  return -(upward_price - downward_price) / (2.0 * bump);
}

double pricing_engine::models::OptionModel::compute_rho(const instruments::Option& option, const market_data::MarketData& market_data) const {
  double interest_rate = market_data.get_interest_rate();
  double bump = 1e-4;

  market_data::MarketData upward_market_data = market_data::MarketData(market_data.get_spot_price(), interest_rate + bump, market_data.get_volatility());
  market_data::MarketData downward_market_data = market_data::MarketData(market_data.get_spot_price(), interest_rate - bump, market_data.get_volatility());
  
  const double upward_price = compute_price(option, upward_market_data);
  const double downward_price = compute_price(option, downward_market_data);
  
  return (upward_price - downward_price) / (2.0 * bump);
}