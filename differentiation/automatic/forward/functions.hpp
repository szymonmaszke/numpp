#ifndef NUMPP_DIFFERENTIATION_AUTOMATIC_FORWARD_FUNCTIONS_HPP_
#define NUMPP_DIFFERENTIATION_AUTOMATIC_FORWARD_FUNCTIONS_HPP_

#include"./structure.hpp"

#if defined  __GNUC__ && !defined __clang__
  #define CONSTEXPR constexpr
#elif
  #define CONSTEXPR
#endif

namespace std{

  template<typename T>
    constexpr auto relu(const numpp::differentiation::automatic::forward<T>& x){
      return numpp::differentiation::automatic::forward<T>{
  /**
    \ingroup numpp_differentiation_forward_automatic

    \brief Calculates rectified linear unit \f$\max(0,x)\f$ of a forward variable
    \param x forward node being passed to ReLU
    \returns Node passed through ReLU
    @{
  */
        ((x.value > 0) ? x.value : 0),
        ((x.value > 0) ? 1 : 0)
      };
    }

  template<typename T>
    CONSTEXPR auto pow(
        const numpp::differentiation::automatic::forward<T>& x,
        const auto& n
        ){
  /**
    \brief Calculates \f$x^n\f$ of a given variable
    \param x forward node from which the power is calculated
    \param n exponent of the power function
    \returns Node passed through power function
  */
      return numpp::differentiation::automatic::forward<T>{
        std::pow(x.value, n),
        x.derivative*(n * std::pow(x.value, n-1))
      };
    }

  template<typename T>
    CONSTEXPR auto exp(const numpp::differentiation::automatic::forward<T>& x){
      return numpp::differentiation::automatic::forward<T>{
  /**
    \brief Calculates \f$e^x\f$ of a given variable
    \param x forward node being the exponent
    \returns Node passed through exponential function
  */
        std::exp(x.value),
        x.derivative * std::exp(x.value)
      };
    }

  template<typename T>
    CONSTEXPR auto log(const numpp::differentiation::automatic::forward<T>& x){
      return numpp::differentiation::automatic::forward<T>{
  /**
    \brief Calculates \f$\ln(x)\f$ of a given variable
    \param x forward node being the logarithm argument
    \returns Node passed through logarithm function
  */
        std::log(x.value),
        x.derivative/x.value
      };
    }
  template<typename T>
    CONSTEXPR auto sin(const numpp::differentiation::automatic::forward<T>& x){
      return numpp::differentiation::automatic::forward<T>{
  /**
    \brief Calculates \f$\sin(x)\f$ of a given variable
    \param x forward node being the sin argument
    \returns Node passed through sin function
  */
        std::sin(x.value),
        x.derivative*cos(x.value)
      };
    }

  template<typename T>
    CONSTEXPR auto cos(const numpp::differentiation::automatic::forward<T>& x){
      return numpp::differentiation::automatic::forward<T>{
  /**
    \brief Calculates \f$\cos(x)\f$ of a given variable
    \param x forward node being the cos argument
    \returns Node passed through cos function
  */
        std::cos(x.value),
        -x.derivative * sin(x.value)
      };
    }

  template<typename T>
    CONSTEXPR auto atan(const numpp::differentiation::automatic::forward<T>& x){
      return numpp::differentiation::automatic::forward<T>{
  /**
    \brief Calculates \f$\arctan(x)\f$ of a given variable
    \param x forward node being the arctan argument
    \returns Node passed through arctan function
  */
        std::atan(x.value),
        x.derivative / (1 + x.value*x.value)
      };
    }

  template<typename T>
    CONSTEXPR auto sqrt(const numpp::differentiation::automatic::forward<T>& x){
      return numpp::differentiation::automatic::forward<T>{
  /**
    \brief Calculates \f$\sqrt(x)\f$ of a given variable
    \param x forward node being the sqrt argument
    \returns Node passed through sqrt function
  */
        std::sqrt(x.value),
        x.derivative / (2 * std::sqrt(x.value))
      };
    }

  template<typename T>
    CONSTEXPR auto asin(const numpp::differentiation::automatic::forward<T>& x){
      return numpp::differentiation::automatic::forward<T>{
  /**
    \brief Calculates \f$\arcsin(x)\f$ of a given variable
    \param x forward node being the asin argument
    \returns Node passed through asin function
  */
        std::asin(x.value),
        x.derivative / std::sqrt(1 - x*x)
      };
    }
  /** @ }*/
}



#endif
