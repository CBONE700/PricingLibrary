#include "../include/instruments/option.h"
#include <stdexcept>
#include <typeinfo>

pricing_engine::instruments::Option::Option(double strike, double time_to_expiration, option_type type) {
  if (strike < 0)
    throw std::invalid_argument("Strike price must be positive.");
  if (time_to_expiration < 0)
    throw std::invalid_argument("Time to expiration cannot be negative.");
  if (typeid(type) != typeid(option_type::call) && typeid(type) != typeid(option_type::put))
    throw std::invalid_argument("Invalid option type.");

  this->strike = strike;
  this->time_to_expiration = time_to_expiration;
  this->type = type;
}