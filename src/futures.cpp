#include "../include/instruments/futures.h"
#include <stdexcept>

pricing_engine::instruments::Future::Future(double pv_income, double carry_rate, double convenience_yield, double time_to_maturity) {
  if (pv_income < 0)
    throw std::invalid_argument("PV income cannot be negative.");
  if (carry_rate < -1.0 || carry_rate > 1.0)
    throw std::invalid_argument("Carry rate must be between -1 and 1.");
  if (convenience_yield < -1.0 || convenience_yield > 1.0)
    throw std::invalid_argument("Convenience yield must be between -1 and 1.");
  if (time_to_maturity < 0)
    throw std::invalid_argument("Time to maturity cannot be negative.");

  this->pv_income = pv_income;
  this->carry_rate = carry_rate;
  this->convenience_yield = convenience_yield;
  this->time_to_maturity = time_to_maturity;
}