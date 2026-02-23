#include "../include/instruments/swap.h"
#include <stdexcept>
#include <typeinfo>

pricing_engine::instruments::Swap::Swap(double fixed_rate, double floating_margin, double time_to_maturity, double notional_value, periodicity period) {
  if (fixed_rate < 0 || fixed_rate > 1)
    throw std::invalid_argument("Fixed rate must be between 0 and 1.");

  if (floating_margin < 0)
    throw std::invalid_argument("Floating margin must be non-negative.");

  if (time_to_maturity < 0)
    throw std::invalid_argument("Time to maturity cannot be negative.");
  if (notional_value < 0)
    throw std::invalid_argument("Notional value must be positive.");
  if (typeid(period) != typeid(periodicity::annual) && typeid(period) != typeid(periodicity::semi_annual) && typeid(period) != typeid(periodicity::quarterly) && typeid(period) != typeid(periodicity::monthly))
    throw std::invalid_argument("Invalid periodicity value.");

  this->fixed_rate = fixed_rate;
  this->floating_margin = floating_margin;
  this->time_to_maturity = time_to_maturity;
  this->notional_value = notional_value;
  this->period = period;
}