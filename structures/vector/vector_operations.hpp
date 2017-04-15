/* #ifndef VECTOR_HPP */
/* #error"This file should only be included by vector.hpp" */
/* #endif */

#ifndef VECTOR_OPERATIONS_HPP_
#define VECTOR_OPERATIONS_HPP_

#include"vector_utils.hpp"
#include<experimental/tuple>

namespace numpp{

  namespace impl{
    template<typename T, typename U, std::size_t Size, bool Transposition, typename Operation, std::size_t... Index>
      constexpr auto accumulate(
          const vector<T,Size,Transposition>& first,
          const vector<U,Size,Transposition>& second,
          Operation&& op,
          std::index_sequence<Index...>
      ){
        return numpp::vector<std::common_type_t<T,U>, Size, Transposition>{
          op(first(Index), second(Index)) ...
        };
    }

    template<typename T, typename U, std::size_t Size, bool Transposition, typename Operation, std::size_t... Index>
      constexpr auto accumulate(
          const vector<T,Size,Transposition>& vec,
          const U scalar,
          Operation&& op,
          std::index_sequence<Index...>
      ){
        return numpp::vector<std::common_type_t<T,U>, Size, Transposition>{
          op(vec(Index), scalar) ...
        };
    }

  }

  //MAIN VECTOR OPERATIONS
	template<typename T, typename U, std::size_t Size, bool Transposition>
		constexpr auto operator+(
				const vector<T,Size,Transposition>& first,
				const vector<U,Size,Transposition>& second
		){
      return impl::accumulate(first, second, std::plus<>{},
          std::make_index_sequence<Size>{});
		}

	template<typename T, typename U, std::size_t Size, bool Transposition>
		constexpr auto operator-(
				const vector<T,Size,Transposition>& first,
				const vector<U,Size,Transposition>& second
		){
      return impl::accumulate(first, second, std::minus<>{},
          std::make_index_sequence<Size>{});
		}


	template<
		typename T,
		typename U,
		std::size_t Size,
		bool Transposition
		/* typename = std::enable_if_t<std::is_arithmetic<U>{}> */
	>
		constexpr auto operator*(
				const vector<T,Size,Transposition>& vec,
				const U scalar
		){
      return impl::accumulate(vec, scalar, std::multiplies<>{},
          std::make_index_sequence<Size>{});
		}


	template<
		typename T,
		typename U,
		std::size_t Size,
		bool Transposition
		/* typename = std::enable_if_t<std::is_arithmetic<U>{}> */
	>
		constexpr auto operator*(
				const U scalar,
				const vector<T,Size,Transposition>& vec
		){
      return vec*scalar;
		}

	template<
		typename T,
		typename U,
		std::size_t Size,
		bool Transposition
		/* typename = std::enable_if_t<std::is_arithmetic<U>{}> */
	>
		constexpr auto operator/(
				const vector<T,Size,Transposition>& vec,
				const U scalar
		){
      return impl::accumulate(vec, scalar, std::divides<>{},
          std::make_index_sequence<Size>{});
		}
}

#endif
