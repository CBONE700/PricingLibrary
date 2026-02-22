#include <iostream>
#include "./include/models/black_scholes_model.h"
#include "./include/instruments/option.h"
#include "./include/market/market_data.h"
#include "./include/instruments/futures.h"
#include "./include/models/futures_model.h"
using namespace std;

int main()
{
  cout << "Welcome to the derivatives pricing engine\n";
  pricing_engine::instruments::option_type type = pricing_engine::instruments::option_type::call;
  pricing_engine::instruments::Option option = pricing_engine::instruments::Option(100, 1, type);
  pricing_engine::market_data::MarketData market_data = pricing_engine::market_data::MarketData(100, 0.05, 0.2);
  pricing_engine::models::BlackScholesModel bsm_engine;
  double bsm_price = bsm_engine.price(option, market_data);
  cout << "Option price: " << bsm_price << endl;
  cout << "Option delta: " << bsm_engine.delta(option, market_data) << endl;
  cout << "Option gamma: " << bsm_engine.gamma(option, market_data) << endl;
  cout << "Option vega: " << bsm_engine.vega(option, market_data) << endl;
  cout << "Option theta: " << bsm_engine.theta(option, market_data) << endl;
  cout << "Option rho: " << bsm_engine.rho(option, market_data) << endl;

  pricing_engine::instruments::Future future = pricing_engine::instruments::Future(0, 0.01, 0.01, 1);
  pricing_engine::models::FuturesModel futures_engine;
  double future_price = futures_engine.price(future, market_data);
  cout << "Future price: " << future_price << endl;
  
  return 0;
}