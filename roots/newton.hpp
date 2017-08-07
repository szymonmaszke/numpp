#ifndef NUMPP_ROOTS_NEWTON_METHOD_HPP_
#define NUMPP_ROOTS_NEWTON_METHOD_HPP_

#include<limits>
#include<cmath>
#include<utility>
#include<experimental/array>
#include"utils.hpp"

namespace numpp::roots{
  //SYMBOLIC VERSION OF THE ALGORITHM
    template<
      typename Function, typename Derivative,
      typename T
    >
      constexpr auto newton(
          T&& value,
          std::size_t iterations=1000,
          const double epsilon = 1e-7
      ){
/** \ingroup numpp_roots

    \brief SYMBOLICAL OVERLOAD

    Newton's algorithm for finding root of the function using first order derivative.

    \tparam T type of function argument
    \tparam Function type of function (has to be symbolic, check: symbolic)
    \tparam Derivative type of derivative (has to be symbolic, check: symbolic)

    \warning Theorethically quadratic convergence when \f$f''\f$ continuous.

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
      typename T
      /* typename = std::enable_if_t<std::is_floating_point<T>::value> */
    >
      constexpr auto newton(
          Function&& f,
          Derivative&& df,
          T&& value,
          std::size_t iterations=1000,
          const double epsilon = 1e-7
      ){
/** \ingroup numpp_roots

    \brief FUNCTOR/FUNCTION OVERLOAD

    \tparam T type of function argument
    \tparam Function type of function (Functor or function)
    \tparam Derivative type of derivative (Functor or function)

    You may use finite difference code from differentiation module

    \sa Finite Difference Differentiation

*/
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
      typename T
      /* typename = std::enable_if_t<std::is_floating_point<T>::value> */
    >
/** \ingroup numpp_roots

    \brief AUTOMATIC DIFFERENTIATION OVERLOAD

    \tparam T type of function argument
    \tparam FunctionAndDerivative Functor returning tuple [value, derivative]
    \tparam Derivative type of derivative (Functor or function)

    \warning FunctionAndDerivative should be of type automatic differentiation forward

    \sa Automatic Differentiation

*/
      constexpr auto newton(
          FunctionAndDerivative&& f,
          T&& value,
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
