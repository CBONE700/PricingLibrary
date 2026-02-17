//Black scholes model header file
#pragma once

#include "../base_class.h"

class BlackScholesModel : public Option {
  double d1;
  double d2;

  double _normal_cdf(double d) const;
  double _calculate_d1(double underlying_price, double strike, double time_to_expiration, double volatility, double risk_free_rate);
  double _calculate_d2(double d1, double volatility, double time_to_expiration);

public:
  explicit BlackScholesModel(double strike, double time_to_expiration, double underlying_price, double volatility, double risk_free_rate, option_type type);
  double get_d1() const { return d1; }
  double get_d2() const { return d2; }
  double get_price() const override;

};