#include<gsl/gsl_deriv.h>
#include <gsl/gsl_math.h>
#include"../../differentiation/forward.hpp"
#include<iostream>
#include<chrono>

class example_function{
  public:
    constexpr double operator()(const double x) const{
      return (12.3*x*x)/std::sqrt(x);
    }
};

double ex_func(const double x, void* params){
  (void)(params); /* avoid unused parameter warning */
  return (12.3*x*x)/std::sqrt(x);
}

int main(){
  //GSL FUNCTION
  auto gsl_begin = std::chrono::high_resolution_clock::now();
  gsl_function F;
  double result, abserr;

  F.function = &ex_func;
  F.params = 0;
  gsl_deriv_forward (&F, 12., 1e-8, &result, &abserr);
  auto gsl_end  = std::chrono::high_resolution_clock::now();
  std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(gsl_end-gsl_begin).count() << "ns" << std::endl;

  std::cout << result << std::endl;
  //NUMPP FUNCTIONS
  auto begin_numpp = std::chrono::high_resolution_clock::now();
  constexpr auto result_numpp = numpp::derivative::forward(example_function{}, 12.);
  auto end_numpp = std::chrono::high_resolution_clock::now();
  std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end_numpp-begin_numpp).count() << "ns" << std::endl;

  std::cout << result_numpp << std::endl;

}
