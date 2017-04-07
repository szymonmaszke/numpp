#ifndef BISECTION_HPP
#define BISECTION_HPP

#include<limits>
#include<cmath>
#include<utility>

namespace numpp{
	namespace root_finding{
		namespace impl{
			template<
				typename T,
				typename Epsilon,
				typename Func
			>
				constexpr auto bisection_find_root(
						Epsilon&& epsilon,
						T&& lower_bound, T&& upper_bound,
						Func&& f, const std::size_t iterations
				){
					auto x = (lower_bound+upper_bound)/2;
          auto root = f(x);

					std::size_t i=0;
					while(epsilon < std::abs(root) && i<iterations){
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
			typename T,
			typename Func,
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
					(std::abs(lower_bound)+std::abs(upper_bound))/2.;

				return impl::bisection_find_root(
						std::move(epsilon),
						std::forward<T>(lower_bound), std::forward<T>(upper_bound),
						std::forward<Func>(f), iterations
				);
			}

		template<
			typename T,
			typename Epsilon,
			typename Func
		>
			constexpr auto bisection(
					Func&& f,
					T&& lower_bound,
					T&& upper_bound,
					std::size_t iterations,
					Epsilon&& epsilon
			){
				return impl::bisection_find_root(
						std::forward<Epsilon>(epsilon),
						std::forward<T>(lower_bound), std::forward<T>(upper_bound),
						std::forward<Func>(f), iterations
				);
			}
	}
}

#endif
