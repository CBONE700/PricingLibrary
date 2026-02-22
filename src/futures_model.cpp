#include "../include/models/futures_model.h"
#include <cmath>
#include <stdexcept>

double pricing_engine::models::FuturesModel::price(const pricing_engine::instruments::Future& future, const pricing_engine::market_data::MarketData& market_data) {
  double adjusted_spot = market_data.get_spot_price() - future.get_pv_income();
  if (adjusted_spot < 0) {
    throw std::invalid_argument("Adjusted spot price cannot be negative.");
  }
  return (adjusted_spot) * std::exp((market_data.get_interest_rate() + future.get_carry_rate() - future.get_convenience_yield()) * future.get_time_to_maturity());
}