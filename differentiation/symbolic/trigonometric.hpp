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
    constexpr auto sin(const T&){
/**
  \ingroup numpp_differentiation_symbolic

  \brief sin returns object representing \f$ \sin(T) \f$
  \tparam T Parameter representing type of the argument (can be complex like log(x))

  \returns Type representing \f$ \sin(T) \f$

  @{
*/
      return sinus<T>{};
    }

  template<typename T>
    constexpr auto cos(const T&){
/**
  \ingroup numpp_differentiation_symbolic

  \brief cos returns object representing \f$ \cos(T) \f$
  \tparam T Parameter representing type of the argument (can be complex like log(x))

  \returns Type representing \f$ \cos(T) \f$

*/
      return cosinus<T>{};
    }

}
#endif
