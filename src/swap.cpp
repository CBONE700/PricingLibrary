#include "../include/instruments/swap.h"
#include <stdexcept>
#include <vector>

pricing_engine::instruments::Swap::Swap(double fixed_rate, double time_to_maturity, double notional_value, periodicity period, std::vector<double> spot_rates) {
  const int payments_per_year = static_cast<int>(period);
  const int total_periods = static_cast<int>(time_to_maturity * payments_per_year + 0.5);

  if (fixed_rate < 0 || fixed_rate > 1)
    throw std::invalid_argument("Fixed rate must be between 0 and 1.");
  if (time_to_maturity <= 0)
    throw std::invalid_argument("Time to maturity cannot be negative.");
  if (spot_rates.size() < static_cast<size_t>(total_periods))
    throw std::invalid_argument("Not enough spot rates provided.");
  for (const double& rate : spot_rates) {
    if (rate < 0)
      throw std::invalid_argument("Spot rates must be non-negative.");
  }
  if (notional_value <= 0)
    throw std::invalid_argument("Notional value must be positive.");

  this->fixed_rate = fixed_rate;
  this->spot_rates = spot_rates;
  this->time_to_maturity = time_to_maturity;
  this->notional_value = notional_value;
  this->period = period;
}