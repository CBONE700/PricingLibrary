#include <iostream>
#include "./include/models/black_scholes_model.h"
#include "./include/models/binomial_model.h"
#include "./include/models/monte_carlo_model.h"
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
  pricing_engine::models::BinomialModel binomial_engine(100);
  pricing_engine::models::MonteCarloModel monte_carlo_engine(1000, 10000);
  double bsm_price = bsm_engine.compute_price(option, market_data);
  double binomial_price = binomial_engine.compute_price(option, market_data);
  double monte_carlo_price = monte_carlo_engine.compute_price(option, market_data);
  cout << "Option price: " << bsm_price << endl;
  cout << "Binomial price: " << binomial_price << endl;
  cout << "Monte Carlo price: " << monte_carlo_price << endl;
  cout << "Option delta: " << bsm_engine.compute_delta(option, market_data) << endl;
  cout << "Binomial delta: " << binomial_engine.compute_delta(option, market_data) << endl;
  cout << "Monte Carlo delta: " << monte_carlo_engine.compute_delta(option, market_data) << endl;
  cout << "Option gamma: " << bsm_engine.compute_gamma(option, market_data) << endl;
  cout << "Binomial gamma: " << binomial_engine.compute_gamma(option, market_data) << endl;
  cout << "Monte Carlo gamma: " << monte_carlo_engine.compute_gamma(option, market_data) << endl;
  cout << "Option vega: " << bsm_engine.compute_vega(option, market_data) << endl;
  cout << "Binomial vega: " << binomial_engine.compute_vega(option, market_data) << endl;
  cout << "Monte Carlo vega: " << monte_carlo_engine.compute_vega(option, market_data) << endl;
  cout << "Option theta: " << bsm_engine.compute_theta(option, market_data) << endl;
  cout << "Binomial theta: " << binomial_engine.compute_theta(option, market_data) << endl;
  cout << "Monte Carlo theta: " << monte_carlo_engine.compute_theta(option, market_data) << endl;
  cout << "Option rho: " << bsm_engine.compute_rho(option, market_data) << endl;
  cout << "Binomial rho: " << binomial_engine.compute_rho(option, market_data) << endl;
  cout << "Monte Carlo rho: " << monte_carlo_engine.compute_rho(option, market_data) << endl;

  pricing_engine::instruments::Future future = pricing_engine::instruments::Future(0, 0.01, 0.01, 1);
  pricing_engine::models::FuturesModel futures_engine;
  double future_price = futures_engine.compute_price(future, market_data);
  cout << "Future price: " << future_price << endl;
  
  return 0;
}