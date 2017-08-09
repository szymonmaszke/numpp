#ifndef NUMPP_DIFFERENTIATION_AUTOMATIC_FORWARD_STRUCTURE_HPP_
#define NUMPP_DIFFERENTIATION_AUTOMATIC_FORWARD_STRUCTURE_HPP_

#include<cmath>
#include<type_traits>

namespace numpp::differentiation::automatic{
/**
\ingroup numpp_differentiation_forward_automatic

\class forward

\tparam T arithmetic type contained in forward class
\warning You have to specialize std::is_arithmetic if you want to use type other than built-ins.

<b> value data member contains function value, derivative data member contains certain derivative </b>

\code
#include"numpp/differentiation/automatic/forward.h"
\endcode


*/
  template<typename T>
    class forward{
      static_assert(std::is_arithmetic<T>(),
          "Current implementation of forward differentiation supports only \
          arithmetic types. Specialize is_arithmetic if your class provides needed overloads"
          );

      public:
        using value_type = T;
				using size_type = std::size_t;

        /** Contains calculated value of an expression*/
        const T value;
        /** Contains calculated derivative of an expression */
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

        template<typename U, typename = std::enable_if_t<std::is_arithmetic<U>::value>>
          constexpr auto operator+(U other){
  /**
    \brief operator+ for built-in arithmetic
  */
            return forward{value + other, derivative};
          }

        constexpr auto operator-(const forward& other){
          return forward{value-other.value, derivative-other.derivative};
        }

        template<typename U, typename = std::enable_if_t<std::is_arithmetic<U>::value>>
          constexpr auto operator-(U other){
  /**
    \brief operator- for built-in arithmetic
  */
            return forward{value - other, derivative};
          }

        template<typename U, typename = std::enable_if_t<std::is_arithmetic<U>::value>>
          constexpr auto operator*(U other){
  /**
    \brief operator* for built-in arithmetic
  */
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

        template<typename U, typename = std::enable_if_t<std::is_arithmetic<U>::value>>
          constexpr auto operator/(U other){
  /**
    \brief operator/ for built-in arithmetic
  */
            return forward{value / other, derivative / other};
          }
    };
}

#endif
