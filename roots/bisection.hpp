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
				return impl::bisection_find_root(
						std::forward<Func>(f),
						std::forward<T>(lower_bound), std::forward<T>(upper_bound),
						epsilon,
            iterations
				);
			}
	}

#endif
