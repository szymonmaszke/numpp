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
    constexpr exponential<T> exp(const T&){
      return exponential<T>{};
    }

  template<typename T>
    constexpr logarithm<T> log(const T&){
      return logarithm<T>{};
    }

}

#endif
