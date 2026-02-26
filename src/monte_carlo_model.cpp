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

double pricing_engine::models::MonteCarloModel::compute_price(
    const pricing_engine::instruments::Option& option,
    const market_data::MarketData& market_data
) const {
    double dt = option.get_time_to_expiration() / steps;
    double nudt = (market_data.get_interest_rate() - 0.5 * market_data.get_volatility() * market_data.get_volatility()) * dt;
    double volsdt = market_data.get_volatility() * std::sqrt(dt);
    double lnS = std::log(market_data.get_spot_price());

    std::mt19937 local_rng = rng;
    std::normal_distribution<double> distribution(0.0, 1.0);

    double sum_Ct = 0.0;
    double sum_Ct2 = 0.0;

    for (int j = 0; j < paths; ++j) {
      double lnSt1 = lnS;
      double lnSt2 = lnS;
        for (int i = 0; i < steps; ++i) {
          double random_value = distribution(local_rng);
          lnSt1 += nudt + volsdt * random_value;
          lnSt2 += nudt - volsdt * random_value;
        }
        double St1 = std::exp(lnSt1);
        double St2 = std::exp(lnSt2);
        double Ct = 0.5 * (
          std::max(
            0.0,
            (option.get_type() == pricing_engine::instruments::option_type::call)
                ? (St1 - option.get_strike())
                : (option.get_strike() - St1)
          ) +
          std::max(
            0.0,
            (option.get_type() == pricing_engine::instruments::option_type::call)
                ? (St2 - option.get_strike())
                : (option.get_strike() - St2)
          )
        );
        sum_Ct += Ct;
        sum_Ct2 += Ct * Ct;
    }

    double C0 = std::exp(-market_data.get_interest_rate() * option.get_time_to_expiration()) * (sum_Ct / paths);
    double sigma = std::sqrt((sum_Ct2 - sum_Ct*sum_Ct/paths) * std::exp(-2.0 * market_data.get_interest_rate() * option.get_time_to_expiration()) / (paths - 1));
    double SE = sigma / std::sqrt(paths);

    return C0;
}
