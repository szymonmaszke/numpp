#ifndef NUMPP_ROOTS_HALLEY_METHOD_HPP_
#define NUMPP_ROOTS_HALLEY_METHOD_HPP_

#include<limits>
#include<cmath>
#include<utility>
#include<experimental/array>
#include"utils.hpp"

namespace numpp::roots{
  //SYMBOLIC VERSION OF THE ALGORITHM
  template<
    typename Function, typename Derivative, typename SecondDerivative,
    typename T
  >
    constexpr auto halley(
        T&& value,
        std::size_t iterations=1000,
        const double epsilon = 1e-7
    ){
        auto argument{value};
        for(std::size_t i=0; i<iterations; ++i){

          auto arr = std::experimental::make_array((argument));
          auto root = Function::calculate(arr);

          if(root < epsilon)
            break;

          auto derivative = Derivative::calculate(arr);
          auto second_derivative = SecondDerivative::calculate(arr);
          argument = argument - (2*root*derivative)
                              / ((2*derivative*derivative) - (root*second_derivative));
        }
        return argument;
    }

  //FOR FINITE DIFFERENCE
  template<
    typename Function, typename Derivative, typename SecondDerivative,
    typename T
  >
    constexpr auto halley(
        T&& value,
        Function f,
        Derivative df,
        SecondDerivative dfdf,
        std::size_t iterations=1000,
        const double epsilon = 1e-7
    ){
        auto argument{value};
        for(std::size_t i=0; i<iterations; ++i){
          auto root = f(argument);
          if(root < epsilon)
            break;
          auto second_derivative = dfdf(argument);
          auto derivative = df(argument);
          argument = argument - (2*root*derivative)
                              / ((2*derivative*derivative) - (root*second_derivative));
        }
        return argument;
    }
}

#endif
