#pragma once

namespace pricing_engine::instruments {
  enum class option_type {call, put};
  enum class option_style {european, american};

  class Option {
    double strike;
    double time_to_expiration;
    option_type type;
    option_style style;

  public:
    explicit Option(double strike, double time_to_expiration, option_type type, option_style style = option_style::european);

    double get_strike() const { return strike; }
    double get_time_to_expiration() const { return time_to_expiration; }
    option_type get_type() const { return type; }
    option_style get_style() const { return style; }
  };
}
