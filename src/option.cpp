#include "../include/instruments/option.h"
#include <stdexcept>

pricing_engine::instruments::Option::Option(double strike, double time_to_expiration, option_type type, option_style style) {
  if (strike < 0)
    throw std::invalid_argument("Strike price must be positive.");
  if (time_to_expiration < 0)
    throw std::invalid_argument("Time to expiration cannot be negative.");
  if (type != option_type::call && type != option_type::put)
    throw std::invalid_argument("Invalid option type.");
  if (style != option_style::european && style != option_style::american)
    throw std::invalid_argument("Invalid option style.");

  this->strike = strike;
  this->time_to_expiration = time_to_expiration;
  this->type = type;
  this->style = style;
}