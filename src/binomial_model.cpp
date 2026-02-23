#include "../include/models/binomial_model.h"
#include <cmath>
#include <vector>

pricing_engine::models::BinomialModel::BinomialModel(int steps) : steps(steps) {
  if (steps <= 0)
    throw std::invalid_argument("Number of steps must be positive.");
}

double pricing_engine::models::BinomialModel::price(const pricing_engine::instruments::Option& option, const market_data::MarketData& market_data) const {
  double dt = option.get_time_to_expiration() / steps;
  double u = std::exp(market_data.get_volatility() * std::sqrt(dt));
  double d = 1.0 / u;
  double p = (std::exp(market_data.get_interest_rate() * dt) - d) / (u - d);
  double discount = std::exp(-market_data.get_interest_rate() * dt);

  std::vector<double> option_values(steps + 1);
  std::vector<double> asset_prices(steps + 1);

  asset_prices[0] = market_data.get_spot_price() * std::pow(d, steps);
  for (int i = 1; i <= steps; ++i) {
      asset_prices[i] = asset_prices[i - 1] * u / d;
  }

  for (int i = 0; i <= steps; ++i) {
      option_values[i] = (option.get_type() == pricing_engine::instruments::option_type::call) ?
                          std::max(0.0, asset_prices[i] - option.get_strike()) :
                          std::max(0.0, option.get_strike() - asset_prices[i]);
  }

  if (option.get_style() == pricing_engine::instruments::option_style::american) {
      for (int step = steps - 1; step >= 0; --step) {
          for (int i = 0; i <= step; ++i) {
              asset_prices[i] = asset_prices[i] / u * d; // move one step back
              double continuation_value = discount * (p * option_values[i + 1] + (1 - p) * option_values[i]);
              double intrinsic_value = (option.get_type() == pricing_engine::instruments::option_type::call) ?
                                      std::max(0.0, asset_prices[i] - option.get_strike()) :
                                      std::max(0.0, option.get_strike() - asset_prices[i]);
              option_values[i] = std::max(continuation_value, intrinsic_value);
          }
      }
  } else {
      for (int step = steps - 1; step >= 0; --step) {
          for (int i = 0; i <= step; ++i) {
              option_values[i] = discount * (p * option_values[i + 1] + (1 - p) * option_values[i]);
          }
      }
  }

  return option_values[0];
}