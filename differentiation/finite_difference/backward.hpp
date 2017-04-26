#ifndef CENTRAL_DERIVATIVE_HPP
#define CENTRAL_DERIVATIVE_HPP

#include<limits>
#include<type_traits>
#include<cmath>

namespace numpp::derivative::finite{
  template<typename Func, typename T>
    constexpr auto backward(Func&& f, T&& x, T&& h){
      return (f(x)-f(x-h))/h;
    }

  template<
    typename Func,
    typename T,
    typename = std::enable_if_t<std::is_floating_point<T>::value>
  >
    constexpr auto backward(Func&& f, T x){
      auto h = x*std::sqrt(std::numeric_limits<T>::epsilon());
      return (f(x)-f(x-h))/h;
    }

  template<
    typename Func,
    typename T,
    typename U,
    typename = std::enable_if_t<
      std::is_floating_point<T>::value and
      std::is_arithmetic<U>::value
    >
  >
    constexpr auto backward(Func&& f, T x, U y){
      auto h = x*std::sqrt(std::numeric_limits<T>::epsilon());
      return (y-f(x-h))/h;
    }

  template<typename Func,typename T,typename U>
    constexpr auto backward(Func&& f, T&& x, U&& y, T&& h){
      return (y-f(x-h))/h;
    }
}

#endif
