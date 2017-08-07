#ifndef NUMPP_ROOTS_BISECTION_HPP_
#define NUMPP_ROOTS_BISECTION_HPP_

#include<limits>
#include<cmath>
#include<utility>
#include"utils.hpp"

namespace numpp::roots{
		namespace impl{
			template<typename T,typename Func>
				constexpr auto bisection_find_root(
            Func&& f,
            T&& lower_bound, T&& upper_bound,
            const double epsilon,
            const std::size_t iterations
				){
					auto x = (lower_bound+upper_bound)/2;
          auto root = f(x);

					std::size_t i=0;
					while(epsilon < impl::abs(root) && i<iterations){
						root = f(x);
            if(root<0)
              lower_bound=x;
            else
              upper_bound=x;

						x=(upper_bound+lower_bound)/2;
						++i;
					}

					return x;
				}
		}

		template<
      typename T, typename Func,
			typename = std::enable_if_t<std::is_floating_point<T>::value>
		>
			constexpr auto bisection(
					Func&& f,
					T lower_bound,
					T upper_bound,
					std::size_t iterations=1000
			){
/** \ingroup numpp_roots

    \brief Bisects given interval and finds the root of function.

    \tparam T type of interval arguments
    \tparam Func type of Function (auto-deduced Functor or function pointer)

    Algorithm stops when it reaches automatically calculated precision
    or exceeds maximum number of iterations (default: 1000)

    Precision adjusted to the lower and upper arguments, accordingly to Numerical Recipees recipe.


*/
				const auto epsilon=
					std::numeric_limits<T>::epsilon()*
					(impl::abs(lower_bound)+impl::abs(upper_bound))/2.;

				return impl::bisection_find_root(
						std::forward<Func>(f),
            std::forward<T>(lower_bound), std::forward<T>(upper_bound),
						epsilon,
            iterations
				);
			}

		template<typename T, typename Func>
			constexpr auto bisection(
					Func&& f,
					T&& lower_bound,
					T&& upper_bound,
					const double epsilon,
          std::size_t iterations
			){
/**
    \overload
    \ingroup numpp_roots

    Everything has to be specified by the user

    Algorithm stops when it reaches precision given by epsilon
    or exceeds iterations provided by the user

*/

				return impl::bisection_find_root(
						std::forward<Func>(f),
						std::forward<T>(lower_bound), std::forward<T>(upper_bound),
						epsilon,
            iterations
				);
			}
	}

#endif
