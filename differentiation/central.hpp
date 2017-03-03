#ifndef CENTRAL_DERIVATIVE_HPP
#define CENTRAL_DERIVATIVE_HPP

#include<limits>
#include<type_traits>
#include<cmath>

namespace numpp{
	namespace derivative{
		template<
			typename Func,
			typename T
		>
			constexpr auto central(Func&& f, T&& x, T&& h){
				return (f(x+0.5*h)-f(x-0.5*h))/h;
			}

		template<
			typename Func,
			typename T,
			typename = std::enable_if_t<std::is_floating_point<T>::value>
		>
			constexpr auto central(Func&& f, T x){
				auto h = x*std::sqrt(std::numeric_limits<T>::epsilon());
				return (f(x+0.5*h)-f(x-0.5*h))/h;
			}
  }
}

#endif
