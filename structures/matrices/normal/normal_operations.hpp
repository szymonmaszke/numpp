#ifndef MATRIX_NORMAL_OPERATIONS_HPP
#define MATRIX_NORMAL_OPERATIONS_HPP

#include"normal_utils.hpp"

namespace numpp::matrix{
  namespace impl{
    template<typename T, typename U, std::size_t Rows, std::size_t Columns, typename Operation, std::size_t... Index>
      constexpr auto accumulate(
          const normal<T,Rows,Columns>& first,
          const normal<U,Rows,Columns>& second,
          Operation&& op,
          std::index_sequence<Index...>
      ){
        return normal<std::common_type_t<T,U>, Rows, Columns>{
          op(get<Index>(first), get<Index>(second)) ...
        };
      }

    template<typename T, typename U, std::size_t Rows, std::size_t Columns, typename Operation, std::size_t... Index>
      constexpr auto accumulate(
          const normal<T,Rows,Columns>& first,
          const U scalar,
          Operation&& op,
          std::index_sequence<Index...>
      ){
        return normal<std::common_type_t<T,U>, Rows, Columns>{
          op(get<Index>(first), scalar) ...
        };
      }
  }

	template<typename T, typename U, std::size_t Rows, std::size_t Columns>
		constexpr auto operator+(
				const normal<T, Rows, Columns>& first,
				const normal<U, Rows, Columns>& second
		){
      return impl::accumulate(first, second, std::plus<>{},
          std::make_index_sequence<Rows*Columns>{});
		}

	template<typename T, typename U, std::size_t Rows, std::size_t Columns>
		constexpr auto operator-(
				const normal<T, Rows, Columns>& first,
				const normal<U, Rows, Columns>& second
		){
      return impl::accumulate(first, second, std::minus<>{},
          std::make_index_sequence<Rows*Columns>{});
		}


	template<
		typename T,
		typename U,
		std::size_t Rows,
		std::size_t Columns
	>
		constexpr auto operator*(
				const normal<T,Rows,Columns>& matrix,
				const U scalar
		){
      return impl::accumulate(matrix, scalar, std::multiplies<>{},
          std::make_index_sequence<Rows*Columns>{});
		}


	template<
		typename T,
		typename U,
		std::size_t Rows,
		std::size_t Columns
	>
		constexpr auto operator*(
				const U scalar,
				const normal<T,Rows,Columns>& vec
		){
      return vec*scalar;
		}

	template<
		typename T,
		typename U,
		std::size_t Rows,
		std::size_t Columns
	>
		constexpr auto operator/(
				const normal<T,Rows,Columns>& vec,
				const U scalar
		){
      return impl::accumulate(vec, scalar, std::divides<>{},
          std::make_index_sequence<Rows*Columns>{});
		}
}


#endif
