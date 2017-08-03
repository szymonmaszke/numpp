#ifndef NUMPP_DIFFERENTIATION_FINITE_CENTRAL_HPP_
#define NUMPP_DIFFERENTIATION_FINITE_CENTRAL_HPP_

#include<limits>
#include<type_traits>
#include<cmath>

namespace numpp::derivative::finite{
  template<typename Func,typename T>
    constexpr auto central(Func&& f, T&& x, T&& h){
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
      auto h = x*std::sqrt(std::numeric_limits<T>::epsilon());
      return (f(x+0.5*h)-f(x-0.5*h))/h;
    }
}

#endif
