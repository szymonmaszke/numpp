#ifndef NUMPP_DIFFERENTIATION_SYMBOLIC_EXPONENTIAL_HPP_
#define NUMPP_DIFFERENTIATION_SYMBOLIC_EXPONENTIAL_HPP_

#include<type_traits>
#include<cmath>
#include"types.hpp"
#include"arithmetic.hpp"
#include"arithmetic_simplifier.hpp"

#if defined  __GNUC__ && !defined __clang__
  #define CONSTEXPR constexpr
#elif
  #define CONSTEXPR
#endif

namespace numpp::differentiation::symbolic{
  template<typename T>
    class logarithm{
      public:
        template<std::size_t Active>
          using derivative = simplify_division<typename T::template derivative<Active>, T>;

        CONSTEXPR static auto calculate(auto&& values){
          return std::log(T::calculate(values));
        }
    };

  template<typename T>
    class exponential{
      public:
        template<std::size_t Active>
        using derivative = simplify_multiplication<exponential<T>, typename T::template derivative<Active>>;

        CONSTEXPR static auto calculate(auto&& values){
          return std::exp(T::calculate(values));
        }
    };

  template<typename T>
    constexpr auto exp(const T&){
/**
  \ingroup numpp_differentiation_symbolic

  \brief exp returns object representing \f$ e^T \f$
  \tparam T Parameter representing type of the exponent (can be complex like sin(x))

  \returns Type representing \f$ e^T \f$

  @{
*/
      return exponential<T>{};
    }

  template<typename T>
    constexpr auto log(const T&){
/**
  \ingroup numpp_differentiation_symbolic

  \brief log returns object representing \f$ \log(T) \f$
  \tparam T Parameter representing type being logarithmized (can be complex like sin(x))

  \returns Type representing \f$ \log(T) \f$

*/
      return logarithm<T>{};
    }

}

#endif
