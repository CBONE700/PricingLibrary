#include "../include/models/swap_model.h"
#include "../include/instruments/swap.h"
#include <cmath>
#include <vector>

double pricing_engine::models::SwapModel::compute_price(
    const pricing_engine::instruments::Swap& swap) {

    size_t periods_to_calculate = static_cast<size_t>(swap.get_spot_rates().size());

    std::vector<double> forward_rates = std::vector<double>(periods_to_calculate);
    forward_rates[0] = swap.get_spot_rates()[0];
 
    for (size_t i = 1; i < periods_to_calculate; ++i) {
        double numerator = pow((1.0 + swap.get_spot_rates()[i]), i + 1);
        double denominator = pow((1.0 + swap.get_spot_rates()[i - 1]), i);
        forward_rates[i] = numerator / denominator - 1.0;
    }

    double floating_leg = 0.0;
    double dt = 1.0 / static_cast<double>(swap.get_periodicity());

    for (size_t i = 0; i < periods_to_calculate; ++i) {
        double t = (i + 1)/static_cast<double>(swap.get_periodicity());
        double discount = 1.0 / (pow(1.0 + swap.get_spot_rates()[i], t));
        floating_leg += forward_rates[i] * swap.get_notional_value() * discount * dt;
    }

    double fixed_leg = 0.0;

    for (size_t i = 0; i < periods_to_calculate; ++i) {
        double t = (i + 1)/static_cast<double>(swap.get_periodicity());
        double discount = 1.0 / pow(1.0 + swap.get_spot_rates()[i], t);
        fixed_leg += swap.get_fixed_rate() * swap.get_notional_value() * discount * dt;
    }

    return fixed_leg - floating_leg;
}
