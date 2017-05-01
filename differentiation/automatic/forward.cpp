#include<cmath>
#include <iostream>
#include<cmath>
#include<type_traits>

//Jerzy Karczmarczuk Foton 2012 numer 117
namespace numpp::differentiation::automatic{
  template<typename T>
    class forward{
      public:
        const T value;
        const T derivative;

        constexpr forward(T&& value, T&& derivative = T{}):
          value{std::forward<T>(value)},
          derivative{std::forward<T>(derivative)}
        {}

        constexpr forward(const forward&) = default;
        constexpr forward(forward&&) = default;

        constexpr auto operator+(const forward& other){
          return forward{
            value+other.value,
            derivative+other.derivative
          };
        }

        //FIX MINUS?
        constexpr auto operator-(const forward& other){
          return forward{value-other.value, derivative-other.derivative};
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
  CONSTEXPR auto exp(numpp::differentiation::automatic::forward<auto> number){
    return numpp::differentiation::automatic::forward{
      std::exp(number.value),
      number.derivative * std::exp(number.value)
    };
  }
  CONSTEXPR auto log(numpp::differentiation::automatic::forward<auto> number){
    return numpp::differentiation::automatic::forward{
      std::log(number.value),
      number.derivative/number.value.
    };
  }
  CONSTEXPR auto sin(numpp::differentiation::automatic::forward<auto> number){
    return numpp::differentiation::automatic::forward{
      std::sin(number.value),
      number.derivative*cos(number.value)
    };
  }

  CONSTEXPR auto cos(numpp::differentiation::automatic::forward<auto> number){
    return numpp::differentiation::automatic::forward{
      std::cos(number.value),
      -number.derivative * sin(number.value)
    };
  }

  CONSTEXPR auto arctan(numpp::differentiation::automatic::forward<auto> number){
    return numpp::differentiation::automatic::forward{
      std::arctan(number.value),
      number.derivative / (1 + number.value*number.value)
    };
  }

  CONSTEXPR auto sqrt(numpp::differentiation::automatic::forward<auto> number){
    return numpp::differentiation::automatic::forward{
      std::sqrt(number.value),
      number.derivative / (2 * std::sqrt(number.value))
    };
  }

  CONSTEXPR auto asin(numpp::differentiation::automatic::forward<auto> number){
    return numpp::differentiation::automatic::forward{
      std::asin(number.value),
      number.derivative / std::sqrt(1 - number*number)
    };
  }
}


int main(){
  using numpp::differentiation::automatic::forward;

  constexpr forward x{2.137,1.};
  constexpr auto result = std::pow(x, 3.) * x;
  std::cout << result.derivative << std::endl;

  return 0;
}
