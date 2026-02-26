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
  };
}