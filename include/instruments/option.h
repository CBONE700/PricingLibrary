#pragma once

namespace pricing_engine::instruments {
  enum class option_type {call, put};

  struct Option {
    double strike;
    double time_to_expiration;
    option_type type;
  };
}
