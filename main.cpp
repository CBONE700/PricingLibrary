#include <iostream>
#include "derivatives_pricing/options_pricing/black_scholes_model/black_scholes_model.h"
using namespace std;

int main()
{
  cout << "Welcome to the derivatives pricing engine\n";
  Option::option_type type = Option::option_type::call;
  BlackScholesModel bsm = BlackScholesModel(100, 1, 100, 0.2, 0.05, type);
  cout << "Option price: " << bsm.get_price() << endl;
  
  return 0;
}