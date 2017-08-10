#ifndef NUMPP_DIFFERENTIATION_FINITE_CENTRAL_HPP_
#define NUMPP_DIFFERENTIATION_FINITE_CENTRAL_HPP_

#include<limits>
#include<type_traits>
#include<cmath>

namespace numpp::differentiation::finite{
  template<typename Func,typename T>
    constexpr auto central(Func&& f, T&& x, T&& h){
  /**
    \defgroup numpp_differentiation_finite_central Central Finite Differentiation
    \ingroup numpp_differentiation_finite

    \brief Calculates central finite derivative \f$\frac{f(x+ 0.5*h)-f(x-0.5*h)}{h}\f$

    \tparam Func Function whose finite difference derivative should be calcuated
    \tparam T Argument type (e.g. double)

    \param f Functor or function whose derivative we want to obtain
    \param x Point where the derivative is calculated
    \param h Disturbtion to x argument, should be around e-7 usually

    \warning If you are unsure about parameter h use function with automatically calculated overload!

    Eventual error performed by this calculation is not provided.

    For better accuracy and numerical stability see:

    \ref numpp_differentiation_symbolic \ref numpp_differentiation_automatic

    \returns Derivative at point x
    @{
  */
      return (f(x+0.5*h)-f(x-0.5*h))/h;
    }

#if defined  __GNUC__ && !defined __clang__
  #define CONSTEXPR constexpr
#elif
  #define CONSTEXPR
#endif

  template<
    typename Func,
    typename T,
    typename = std::enable_if_t<std::is_floating_point<T>::value>
  >
    CONSTEXPR auto central(Func&& f, T x){
  /**
    \overload

    Automatically calculated disturbtion h to argument x, taken from Numerical Recipees (add source)

  */
      auto h = x*std::sqrt(std::numeric_limits<T>::epsilon());
      return (f(x+0.5*h)-f(x-0.5*h))/h;
    }
}

#endif
