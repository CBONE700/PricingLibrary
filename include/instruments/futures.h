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

    void set_pv_income(double new_pv_income) { pv_income = new_pv_income; }
    void set_carry_rate(double new_carry_rate) { carry_rate = new_carry_rate; }
    void set_convenience_yield(double new_convenience_yield) { convenience_yield = new_convenience_yield; }
    void set_time_to_maturity(double new_time_to_maturity) { time_to_maturity = new_time_to_maturity; }
  };
}