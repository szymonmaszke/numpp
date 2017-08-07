#ifndef NUMPP_DIFFERENTIATION_SYMBOLIC_ARITHMETIC_HPP_
#define NUMPP_DIFFERENTIATION_SYMBOLIC_ARITHMETIC_HPP_

#include<cmath>
#include<type_traits>

#include"types.hpp"
#include"arithmetic_simplifier.hpp"

#if defined  __GNUC__ && !defined __clang__
  #define CONSTEXPR constexpr
#elif
  #define CONSTEXPR
#endif

/* 'Abandon All Hope, Ye Who Enter Here' ~XTerm README */

namespace numpp::differentiation::symbolic{
  template<typename T> class minus;
  template<typename Left, typename Right> class subtract;

  template<typename Left, typename Right> class add;
  template<typename Left, typename Right> class multiply;
  template<typename Left, typename Right> class divide;

  template<typename Left, int Exp>
    class power{
      public:
        template<std::size_t Active>
          using derivative = simplify_multiplication<
                              multiply<constant<Exp>, power<Left, Exp-1>>,
                              typename Left::template derivative<Active>
                             >;
        CONSTEXPR static auto calculate(auto&& values){
          return std::pow(Left::calculate(values), Exp);
        }
    };

  template<typename Left, typename Right>
    class divide{
      public:
        template<std::size_t Active>
          using derivative =
                simplify_division<
                  simplify_subtraction<
                    simplify_multiplication<typename Left::template derivative<Active>, Right>,
                    simplify_multiplication<Left, typename Right::template derivative<Active>>>,
                  power<Right, 2>
                >;

        CONSTEXPR static auto calculate(auto&& values){
          return Left::calculate(values) / Right::calculate(values);
        }
    };

  template<typename Left, typename Right>
    class multiply{
      public:
        template<std::size_t Active>
          using derivative =
                simplify_addition<
                  simplify_multiplication<
                    typename Left::template derivative<Active>,
                    Right
                  >,
                  simplify_multiplication<
                    Left,
                    typename Right::template derivative<Active>
                  >
                >;

        CONSTEXPR static auto calculate(auto&& values){
          return Left::calculate(values) * Right::calculate(values);
        }
    };


  template<typename Left, typename Right>
    class add{
      public:
        template<std::size_t Active>
          using derivative = simplify_addition<
                              typename Left::template derivative<Active>,
                              typename Right::template derivative<Active>
                             >;

        CONSTEXPR static auto calculate(auto&& values){
          return Left::calculate(values) + Right::calculate(values);
        }
    };

  template<typename Left, typename Right>
    class subtract{
      public:
        template<std::size_t Active>
          using derivative = simplify_subtraction<
                              typename Left::template derivative<Active>,
                              typename Right::template derivative<Active>
                             >;

        CONSTEXPR static auto calculate(auto&& values){
          return Left::calculate(values) - Right::calculate(values);
        }

    };

  template<typename T>
    class minus{
      public:
        template<std::size_t Active>
          using derivative = simplify_minus<typename T::template derivative<Active>>;

        CONSTEXPR static auto calculate(auto&& values){
          return - T::calculate(values);
        }

    };

  //TEMPLATE OVERLOADS FOR READABILITY

  template<typename Left, typename Right>
    constexpr add<Left, Right> operator+(const Left&, const Right&){
      return add<Left, Right>{};
    }

  template<typename Left, typename Right>
    constexpr auto operator-(const Left&, const Right&){
      return simplify_subtraction<Left, Right>{};
    }

  template<typename T>
    constexpr auto operator-(const T&){
      return simplify_minus<T>{};
    }

  template<typename Left, typename Right>
    constexpr auto operator*(const Left&, const Right&){
      return simplify_multiplication<Left, Right>{};
    }

  template<typename Left, typename Right>
    constexpr auto operator/(const Left&, const Right&){
      return divide<Left, Right>{};
    }

}

#endif
