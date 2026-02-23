#include "../include/models/swap_model.h"
#include <cmath>

double pricing_engine::models::SwapModel::price(
    const instruments::Swap& swap,
    const market_data::MarketData& market_data) {

    double fixed_leg = 0.0;
    double r = market_data.get_interest_rate();
    double dt = 1.0 / static_cast<double>(swap.get_periodicity());
    int n = swap.get_time_to_maturity() * static_cast<int>(swap.get_periodicity());

    for (int i = 0; i < n; ++i) {
        double t = (i + 1) * dt;
        double discount = std::exp(-r * t);  // continuous discounting preferred
        fixed_leg += swap.get_fixed_rate() * swap.get_notional_value() * dt * discount;
    }

    double maturity = swap.get_time_to_maturity();
    double discount_T = std::exp(-r * maturity);

    double floating_leg = swap.get_notional_value() * (1.0 - discount_T);

    return fixed_leg - floating_leg;
}
