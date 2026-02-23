#pragma once

namespace pricing_engine::instruments {
  enum class periodicity {annual = 1, semi_annual = 2, quarterly = 4, monthly = 12};

  class Swap {
    double fixed_rate;
    double floating_margin;
    double time_to_maturity;
    double notional_value;
    periodicity period;

  public:
    explicit Swap(double fixed_rate, double floating_margin, double time_to_maturity, double notional_value, periodicity period);

    double get_fixed_rate() const { return fixed_rate; }
    double get_floating_margin() const { return floating_margin; }
    double get_time_to_maturity() const { return time_to_maturity; }
    double get_notional_value() const { return notional_value; }
    periodicity get_periodicity() const { return period; }

    void set_fixed_rate(double new_fixed_rate) { fixed_rate = new_fixed_rate; }
    void set_floating_margin(double new_floating_margin) { floating_margin = new_floating_margin; }
    void set_time_to_maturity(double new_time_to_maturity) { time_to_maturity = new_time_to_maturity; }
    void set_notional_value(double new_notional_value) { notional_value = new_notional_value; }
    void set_periodicity(periodicity new_periodicity) { period = new_periodicity; }
  };
}