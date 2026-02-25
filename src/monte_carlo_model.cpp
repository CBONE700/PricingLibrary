#include  "../include/models/monte_carlo_model.h"
#include "../include/market/market_data.h"
#include <algorithm>
#include <cmath>
#include <random>
#include <stdexcept>

pricing_engine::models::MonteCarloModel::MonteCarloModel(int steps, int paths) {
  if (steps <= 0)
    throw std::invalid_argument("Number of steps must be positive.");
  if (paths <= 0)
    throw std::invalid_argument("Number of paths must be positive.");
  this->steps = steps;
  this->paths = paths;

  unsigned int seed = std::random_device{}();
  this->rng = std::mt19937(seed);
}

double pricing_engine::models::MonteCarloModel::price(
    const pricing_engine::instruments::Option& option,
    const market_data::MarketData& market_data
) const {
    double dt = option.get_time_to_expiration() / steps;
    double nudt = (market_data.get_interest_rate() - 0.5 * market_data.get_volatility() * market_data.get_volatility()) * dt;
    double volsdt = market_data.get_volatility() * std::sqrt(dt);

    std::mt19937 local_rng = rng;
    std::normal_distribution<double> distribution(0.0, 1.0);

    double sum_Ct = 0.0;
    double lnSt = std::log(market_data.get_spot_price());

    for (int j = 0; j < paths; ++j) {
        for (int i = 0; i < steps; ++i) {
            lnSt += nudt + volsdt * distribution(local_rng);
        }
        double St = std::exp(lnSt);
        double Ct = std::max(
            0.0,
            (option.get_type() == pricing_engine::instruments::option_type::call)
                ? (St - option.get_strike())
                : (option.get_strike() - St)
        );
        sum_Ct += Ct;
    }

    return std::exp(-market_data.get_interest_rate() * option.get_time_to_expiration()) * (sum_Ct / paths);
}
