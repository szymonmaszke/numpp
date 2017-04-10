
/* #ifndef VECTOR_HPP */
/* #error"This file should only be included by matrix::normal.hpp" */
/* #endif */

#ifndef VECTOR_OPERATIONS_HPP_
#define VECTOR_OPERATIONS_HPP_

#include"normal_utils.hpp"
#include<experimental/tuple>

namespace numpp{

  //UOGOLNIC, MOZLIWA DUPLIKACJA KODU (vector, macierze, dodaje do utils)
  namespace impl{
    template<typename T, typename U, std::size_t Rows, std::size_t Columns, typename Operation, std::size_t... Index>
      constexpr auto accumulate(
          const matrix::normal<T,Rows,Columns>& first,
          const matrix::normal<T,Rows,Columns>& second,
          Operation&& op,
          std::index_sequence<Index...>
      ){
        return matrix::normal<std::common_type_t<T,U>, Rows, Columns>{
          op(matrix::get<Index>(first), matrix::get<Index>(second)) ...
        };
    }
    template<typename T, typename U, std::size_t Rows, std::size_t Columns, typename Operation, std::size_t... Index>
      constexpr auto accumulate(
          const matrix::normal<T,Rows,Columns>& first,
          const U scalar,
          Operation&& op,
          std::index_sequence<Index...>
      ){
        return matrix::normal<std::common_type_t<T,U>, Rows, Columns>{
          op(matrix::get<Index>(first), scalar) ...
        };

      }
  }

  //MAIN VECTOR OPERATIONS
	template<typename T, typename U, std::size_t Rows, std::size_t Columns>
		constexpr auto operator+(
				const matrix::normal<T, Rows, Columns>& first,
				const matrix::normal<U, Rows, Columns>& second
		){
      return impl::accumulate(first, second, std::plus<>{},
          std::make_index_sequence<Rows*Columns>{});
		}

	template<typename T, typename U, std::size_t Rows, std::size_t Columns>
		constexpr auto operator-(
				const matrix::normal<T, Rows, Columns>& first,
				const matrix::normal<U, Rows, Columns>& second
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
				const matrix::normal<T,Rows,Columns>& matrix,
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
				const matrix::normal<T,Rows,Columns>& vec
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
				const matrix::normal<T,Rows,Columns>& vec,
				const U scalar
		){
      return impl::accumulate(vec, scalar, std::divides<>{},
          std::make_index_sequence<Rows*Columns>{});
		}
}


#endif
