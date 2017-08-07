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
/** \ingroup numpp_roots

    \brief SYMBOLICAL OVERLOAD:

    Halley's algorithm for finding root of the function using first and second order derivatives.

    \tparam T type of function argument
    \tparam Function type of function (has to be symbolic, check: symbolic)
    \tparam Derivative type of derivative (has to be symbolic, check: symbolic)
    \tparam SecondDerivative type of second derivative (has to be symbolic, check: symbolic)

    \warning Theorethically cubic convergence when \f$f'''\f$ continuous.

    \warning Some problems may arise for this method, check professional literature

    Algorithm stops when it reaches given precision
    or exceeds maximum number of iterations (default: 1000)

    \return <b>Type</b>: Same as Function return type
    \return <b>Value</b>: Root in the case of convergence

    \warning <b>May not converge to the root, evaluate your result after obtaining it</b>

    \sa Symbolic Differentiation


*/
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

/** \ingroup numpp_roots

    \brief FINITE DIFFERENCE/OTHER METHODS OVERLOAD

    \tparam T type of function argument
    \tparam Function type of function (Functor or function)
    \tparam Derivative type of derivative (Functor of function)
    \tparam SecondDerivative type of second derivative (Functor or function)

*/
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
