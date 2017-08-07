#ifndef NUMPP_DIFFERENTIATION_SYMBOLIC_TRIGONOMETRIC_HPP_
#define NUMPP_DIFFERENTIATION_SYMBOLIC_TRIGONOMETRIC_HPP_

#include<type_traits>
#include<cmath>

#include"arithmetic.hpp"

#if defined  __GNUC__ && !defined __clang__
#define CONSTEXPR constexpr
#elif
#define CONSTEXPR
#endif

namespace numpp::differentiation::symbolic{
  template<typename T> class cosinus;
  template<typename T>
    class sinus{
      public:
        template<std::size_t Active>
          using derivative = simplify_multiplication<
          cosinus<T>,
          typename T::template derivative<Active>
            >;

        CONSTEXPR static auto calculate(auto&& values){
          return std::sin(T::calculate(values));
        }
    };

  template<typename T>
    class cosinus{
      public:
        template<std::size_t Active>
          using derivative =
            simplify_multiplication<
              simplify_minus<sinus<T>>,
              typename T::template derivative<Active>
            >;

        CONSTEXPR static auto calculate(auto&& values){
          return std::cos(T::calculate(values));
        }
    };

  template<typename T>
    constexpr sinus<T> sin(const T&){
      return sinus<T>{};
    }

  template<typename T>
    constexpr cosinus<T> cos(const T&){
      return cosinus<T>{};
    }

}
#endif
