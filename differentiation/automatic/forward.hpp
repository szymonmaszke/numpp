#include<cmath>
#include<iostream>
#include<cmath>
#include<type_traits>

//Jerzy Karczmarczuk Foton 2012 numer 117
//ADD n-th ORDER DERIVATIVE
//ADD cast operators

namespace numpp::differentiation::automatic{
  template<typename T>
    class forward{

      static_assert(std::is_arithmetic<T>(),
          "Current implementation of forward differentiation supports only \
          arithmetic types. Specialize is_arithmetic if your class may be equal to 1"
          );

      public:
        using value_type = T;
				using size_type = std::size_t;

        const T value;
        const T derivative;

        constexpr forward(T value, T derivative = 1):
            value{value},
            derivative{derivative}
        {}

        constexpr forward(const forward&) = default;
        constexpr forward(forward&&) = default;
        constexpr forward& operator=(const forward&) = default;
        constexpr forward& operator=(forward&&) = default;

        constexpr auto operator+(const forward& other){
          return forward{
            value+other.value,
            derivative+other.derivative
          };
        }

        constexpr auto operator-(const forward& other){
          return forward{value-other.value, derivative-other.derivative};
        }

        template<typename U>
          constexpr auto operator*(U&& other){
            return forward{value * other, derivative * other};
          }

        constexpr auto operator*(const forward& other){
          return forward{
            value * other.value,
            derivative*other.value + value*other.derivative
          };
        }

        constexpr auto operator/(const forward& other){
          return forward{
            value/other.value,
            (derivative*other.value - value*other.derivative)
              /(other.value*other.value)
          };
        }
    };
}


#if defined  __GNUC__ && !defined __clang__
  #define CONSTEXPR constexpr
#elif
  #define CONSTEXPR
#endif

namespace std{

  CONSTEXPR auto relu(const numpp::differentiation::automatic::forward<auto>& number){
    return numpp::differentiation::automatic::forward{
      std::max(0, number.value),
      (((number.value) > 0) ? 1 : 0)
    };
  }

  CONSTEXPR auto pow(
      const numpp::differentiation::automatic::forward<auto>& number,
      const auto& exp
      ){
    return numpp::differentiation::automatic::forward{
      std::pow(number.value, exp),
      number.derivative*(exp * std::pow(number.value, exp-1))
    };
  }

  CONSTEXPR auto exp(const numpp::differentiation::automatic::forward<auto>& number){
    return numpp::differentiation::automatic::forward{
      std::exp(number.value),
      number.derivative * std::exp(number.value)
    };
  }
  CONSTEXPR auto log(const numpp::differentiation::automatic::forward<auto>& number){
    return numpp::differentiation::automatic::forward{
      std::log(number.value),
      number.derivative/number.value
    };
  }
  CONSTEXPR auto sin(const numpp::differentiation::automatic::forward<auto>& number){
    return numpp::differentiation::automatic::forward{
      std::sin(number.value),
      number.derivative*cos(number.value)
    };
  }

  CONSTEXPR auto cos(const numpp::differentiation::automatic::forward<auto>& number){
    return numpp::differentiation::automatic::forward{
      std::cos(number.value),
      -number.derivative * sin(number.value)
    };
  }

  CONSTEXPR auto arctan(const numpp::differentiation::automatic::forward<auto>& number){
    return numpp::differentiation::automatic::forward{
      std::arctan(number.value),
      number.derivative / (1 + number.value*number.value)
    };
  }

  CONSTEXPR auto sqrt(const numpp::differentiation::automatic::forward<auto>& number){
    return numpp::differentiation::automatic::forward{
      std::sqrt(number.value),
      number.derivative / (2 * std::sqrt(number.value))
    };
  }

  CONSTEXPR auto asin(const numpp::differentiation::automatic::forward<auto>& number){
    return numpp::differentiation::automatic::forward{
      std::asin(number.value),
      number.derivative / std::sqrt(1 - number*number)
    };
  }
}
