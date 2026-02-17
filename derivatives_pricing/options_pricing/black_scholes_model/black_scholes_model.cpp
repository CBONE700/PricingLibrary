#include "black_scholes_model.h"
#include <cmath>

BlackScholesModel::BlackScholesModel(double strike, double maturity, double underlying_price, double volatility, double risk_free_rate, option_type type)
: Option(strike, maturity, underlying_price, volatility, risk_free_rate, type) {
  d1 = _calculate_d1(underlying_price, strike, maturity, volatility, risk_free_rate);
  d2 = _calculate_d2(d1, volatility, maturity);
}

double BlackScholesModel::_normal_cdf(double d) const {
  return 0.5 * std::erfc(-d * M_SQRT1_2);
}

double BlackScholesModel::_calculate_d1(double underlying_price, double strike, double maturity, double volatility, double risk_free_rate) {
  double numerator = std::log(underlying_price / strike) + maturity * (risk_free_rate + 0.5 * volatility * volatility);
  double denominator = volatility * std::sqrt(maturity);
  return numerator / denominator;
}

double BlackScholesModel::_calculate_d2(double d1, double volatility, double) {
  return d1 - volatility * std::sqrt(_time_to_expiration);
}

double BlackScholesModel::get_price() const {
  double price;
  if (_option_type == option_type::call) {
    price = _underlying_price * _normal_cdf(d1) - _strike * std::exp(-_risk_free_rate * _time_to_expiration) * _normal_cdf(d2);
  } else {
    price = _strike * std::exp(-_risk_free_rate * _time_to_expiration) * _normal_cdf(-d2) - _underlying_price * _normal_cdf(-d1);
  }
  return price;
}

