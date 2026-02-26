#pragma once

namespace pricing_engine::instruments {
  class Future {
    //TODO: Think about how to handle income and cost of carry properly.
    double pv_income;
    double carry_rate;
    double convenience_yield;
    double time_to_maturity;

  public:
    explicit Future(double pv_income, double carry_rate, double convenience_yield, double time_to_maturity);

    double get_pv_income() const { return pv_income; }
    double get_carry_rate() const { return carry_rate; }
    double get_convenience_yield() const { return convenience_yield; }
    double get_time_to_maturity() const { return time_to_maturity; }
  };
}