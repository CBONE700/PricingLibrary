//Black scholes model header file
#pragma once

#include "../base_class.h"

class BlackScholesModel : public Option {
  double d1;
  double d2;

public:
  BlackScholesModel(double strike, double maturity, double underlying_price, double volatility, double risk_free_rate, option_type type);

  double normal_cdf(double d) const;
  double calculate_d1();
  double calculate_d2();

  const double& get_d1() const;
  const double& get_d2() const;
};