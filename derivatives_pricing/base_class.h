//Base class for all derivatives
#pragma once

class Derivative {
  public:
    virtual ~Derivative() = default;
    virtual double get_price() const = 0;
};