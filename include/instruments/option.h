#pragma once

namespace pricing_engine::instruments {
  enum class option_type {call, put};

  class Option {
    double strike;
    double time_to_expiration;
    option_type type;

  public:
    explicit Option(double strike, double time_to_expiration, option_type type);

    double get_strike() const { return strike; }
    double get_time_to_expiration() const { return time_to_expiration; }
    option_type get_type() const { return type; }

    void set_strike(double new_strike) { strike = new_strike; }
    void set_time_to_expiration(double new_time_to_expiration) { time_to_expiration = new_time_to_expiration; }
    void set_type(option_type new_type) { type = new_type; }
  };
}
