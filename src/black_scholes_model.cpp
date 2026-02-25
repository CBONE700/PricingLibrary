#include "../include/models/black_scholes_model.h"
#include "../include/market/market_data.h"
#include <cmath>
#include <numbers>
#include <stdexcept>

double pricing_engine::models::BlackScholesModel::normal_cdf(double d) const {
  return 0.5 * std::erfc(-d / std::sqrt(2.0));
}

double pricing_engine::models::BlackScholesModel::normal_pdf(double d) const {
  return (1.0 / (double)pow(2 * std::numbers::pi, 0.5)) * std::exp(-0.5 * d * d);
}

double pricing_engine::models::BlackScholesModel::calculate_d1(double underlying_price, double strike, double time_to_expiration, double volatility, double risk_free_rate) const {
  double numerator = std::log(underlying_price / strike) + time_to_expiration * (risk_free_rate + 0.5 * volatility * volatility);
  double denominator = volatility * std::sqrt(time_to_expiration);
  return numerator / denominator;
}

double pricing_engine::models::BlackScholesModel::calculate_d2(double d1, double volatility, double time_to_expiration) const {
  return d1 - volatility * std::sqrt(time_to_expiration);
}

double pricing_engine::models::BlackScholesModel::price(const pricing_engine::instruments::Option& option, const pricing_engine::market_data::MarketData& market_data) const {
  if (option.get_style() != pricing_engine::instruments::option_style::european) {
    throw std::invalid_argument("Black-Scholes model only supports European options.");
  }

  double d1 = calculate_d1(market_data.get_spot_price(), option.get_strike(), option.get_time_to_expiration(), market_data.get_volatility(), market_data.get_interest_rate());
  double d2 = calculate_d2(d1, market_data.get_volatility(), option.get_time_to_expiration());

  double price;
  if (option.get_type() == pricing_engine::instruments::option_type::call) {
    price = market_data.get_spot_price() * normal_cdf(d1) - option.get_strike() * std::exp(-market_data.get_interest_rate() * option.get_time_to_expiration()) * normal_cdf(d2);
  } else {
    price = option.get_strike() * std::exp(-market_data.get_interest_rate() * option.get_time_to_expiration()) * normal_cdf(-d2) - market_data.get_spot_price() * normal_cdf(-d1);
  }
  return price;
}

double pricing_engine::models::BlackScholesModel::delta(const instruments::Option& option, const market_data::MarketData& market_data) const {
  if (option.get_style() != pricing_engine::instruments::option_style::european) {
    throw std::invalid_argument("Black-Scholes model only supports European options.");
  }
  if (option.get_type() == pricing_engine::instruments::option_type::call) {
    return normal_cdf(calculate_d1(market_data.get_spot_price(), option.get_strike(), option.get_time_to_expiration(), market_data.get_volatility(), market_data.get_interest_rate()));
  } else {
    return normal_cdf(calculate_d1(market_data.get_spot_price(), option.get_strike(), option.get_time_to_expiration(), market_data.get_volatility(), market_data.get_interest_rate())) - 1.0;
  }
}

double pricing_engine::models::BlackScholesModel::gamma(const instruments::Option& option, const market_data::MarketData& market_data) const {
  if (option.get_style() != pricing_engine::instruments::option_style::european) {
    throw std::invalid_argument("Black-Scholes model only supports European options.");
  }
  double d1 = calculate_d1(market_data.get_spot_price(), option.get_strike(), option.get_time_to_expiration(), market_data.get_volatility(), market_data.get_interest_rate());
  return normal_pdf(d1) / (market_data.get_spot_price() * market_data.get_volatility() * std::sqrt(option.get_time_to_expiration()));
}

double pricing_engine::models::BlackScholesModel::vega(const instruments::Option& option, const market_data::MarketData& market_data) const {
  if (option.get_style() != pricing_engine::instruments::option_style::european) {
    throw std::invalid_argument("Black-Scholes model only supports European options.");
  }
  double d1 = calculate_d1(market_data.get_spot_price(), option.get_strike(), option.get_time_to_expiration(), market_data.get_volatility(), market_data.get_interest_rate());
  return market_data.get_spot_price() * normal_pdf(d1) * std::sqrt(option.get_time_to_expiration());
}

double pricing_engine::models::BlackScholesModel::theta(const instruments::Option& option, const market_data::MarketData& market_data) const {
  if (option.get_style() != pricing_engine::instruments::option_style::european) {
    throw std::invalid_argument("Black-Scholes model only supports European options.");
  }
  double d1 = calculate_d1(market_data.get_spot_price(), option.get_strike(), option.get_time_to_expiration(), market_data.get_volatility(), market_data.get_interest_rate());
  double d2 = calculate_d2(d1, market_data.get_volatility(), option.get_time_to_expiration());

  double theta;
  if (option.get_type() == pricing_engine::instruments::option_type::call) {
    theta = - (market_data.get_spot_price() * normal_pdf(d1) * market_data.get_volatility()) / (2.0 * std::sqrt(option.get_time_to_expiration())) - market_data.get_interest_rate() * option.get_strike() * std::exp(-market_data.get_interest_rate() * option.get_time_to_expiration()) * normal_cdf(d2);
  } else {
    theta = - (market_data.get_spot_price() * normal_pdf(d1) * market_data.get_volatility()) / (2.0 * std::sqrt(option.get_time_to_expiration())) + market_data.get_interest_rate() * option.get_strike() * std::exp(-market_data.get_interest_rate() * option.get_time_to_expiration()) * normal_cdf(-d2);
  }
  return theta;
}

double pricing_engine::models::BlackScholesModel::rho(const instruments::Option& option, const market_data::MarketData& market_data) const {
  if (option.get_style() != pricing_engine::instruments::option_style::european) {
    throw std::invalid_argument("Black-Scholes model only supports European options.");
  }
  double d1 = calculate_d1(market_data.get_spot_price(), option.get_strike(), option.get_time_to_expiration(), market_data.get_volatility(), market_data.get_interest_rate());
  double d2 = calculate_d2(d1, market_data.get_volatility(), option.get_time_to_expiration());

  double rho;
  if (option.get_type() == pricing_engine::instruments::option_type::call) {
    rho = option.get_strike() * option.get_time_to_expiration() * std::exp(-market_data.get_interest_rate() * option.get_time_to_expiration()) * normal_cdf(d2);
  } else {
    rho = -option.get_strike() * option.get_time_to_expiration() * std::exp(-market_data.get_interest_rate() * option.get_time_to_expiration()) * normal_cdf(-d2);
  }
  return rho;
}