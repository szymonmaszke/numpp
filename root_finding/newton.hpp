#ifndef NUMPP_ROOT_FINDING_NEWTON_METHOD_HPP_
#define NUMPP_ROOT_FINDING_NEWTON_METHOD_HPP_

#include<limits>
#include<cmath>
#include<utility>
#include<experimental/array>

namespace numpp::roots{
  //SYMBOLIC VERSION OF THE ALGORITHM
  namespace impl{
    constexpr auto abs(auto value){
      return value < 0 ? -value : value;
    }

  }
  template<
    typename Function, typename Derivative,
    typename T
  >
    constexpr auto newton(
        T&& value,
        std::size_t iterations=1000,
        const double epsilon = 1e-7
    ){
        auto argument{value};
        for(std::size_t i=0; i<iterations; ++i){
          auto root = Function::calculate(std::experimental::make_array(argument));
          auto derivative = Derivative::calculate(std::experimental::make_array(argument));
          if(impl::abs(derivative) < epsilon || root < epsilon)
            break;
          argument = argument - root/derivative;
        }
        return argument;
    }

  //FOR FINITE DIFFERENCE
  template<
    typename Function, typename Derivative,
    typename T,
    typename = std::enable_if_t<std::is_floating_point<T>::value>
  >
    constexpr auto newton(
        T&& value,
        Function f,
        Derivative df,
        std::size_t iterations=1000,
        const double epsilon = 1e-7
    ){
        auto argument{value};
        for(std::size_t i=0; i<iterations; ++i){
          auto root = f(argument);
          auto derivative = df(argument);
          if(impl::abs(derivative) < epsilon || root < epsilon)
            break;
          argument = argument - root/derivative;
        }
        return argument;
    }

  //FOR AUTOMATIC DIFFERENTIATION METHOD
  template<
    typename FunctionAndDerivative,
    typename T,
    typename = std::enable_if_t<std::is_floating_point<T>::value>
  >
    constexpr auto newton(
        T&& value,
        FunctionAndDerivative f,
        std::size_t iterations=1000,
        const double epsilon = 1e-7
    ){
        auto argument{value};
        for(std::size_t i=0; i<iterations; ++i){
          auto [root, derivative] = f(argument);
          if(impl::abs(derivative) < epsilon || root < epsilon)
            break;
          argument = argument - root/derivative;
        }
        return argument;
    }
}

#endif
