//Base class for options specific implementations, inhereting from the general derivative base class
#pragma once

#include "../base_class.h"

class Option : public Derivative {
public:
  enum class option_type { call, put };
  // Default option pricing constructor
  explicit Option(double strike, double time_to_expiration, double underlying_price, double volatility, double risk_free_rate, option_type type)
  : _strike(strike), _time_to_expiration(time_to_expiration), _underlying_price(underlying_price), _volatility(volatility), _risk_free_rate(risk_free_rate), _option_type(type) {}

  //Setter methods for all input variables
  void set_strike(double value) {_strike = value;}
  void set_time_to_expiration(double value) {_time_to_expiration = value;}
  void set_underlying_price(double value) {_underlying_price = value;}
  void set_volatility(double value) {_volatility = value;}
  void set_risk_free_rate(double value) {_risk_free_rate = value;}
  void set_option_type(option_type value) {_option_type = value;}


  //Getter methods for all input variables
  double get_strike() const { return _strike; }
  double get_time_to_expiration() const { return _time_to_expiration; }
  double get_underlying_price() const { return _underlying_price; }
  double get_volatility() const { return _volatility; }
  double get_risk_free_rate() const { return _risk_free_rate; }
  option_type get_option_type() const {return _option_type; }
protected:
  // Inputs into all option pricing models
  double _strike;
  double _time_to_expiration;
  double _underlying_price;
  double _volatility;
  double _risk_free_rate;
  option_type _option_type;
};