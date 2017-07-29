#ifndef NUMPP_MATRIX_DENSE_FUNCTIONS_HPP_
#define NUMPP_MATRIX_DENSE_FUNCTIONS_HPP_

#include"./normal_operations.hpp"
#include<cmath>

namespace numpp::matrix{
  namespace impl{
    template<typename T, std::size_t Rows, std::size_t Columns, std::size_t... Index>
      constexpr auto transpose_row_expand(
          const normal<T,Rows,Columns>& matrix,
          std::size_t column,
          std::index_sequence<Index...>
          ){
        return std::make_tuple(
            matrix(Index, column) ...
            );
      }

    template<typename T, std::size_t Rows, std::size_t Columns, std::size_t... Index>
      constexpr auto transpose_column_expand(
          const normal<T,Rows, Columns>& matrix,
          std::index_sequence<Index...>
          ){
        return std::tuple_cat(
            transpose_row_expand(matrix, Index, std::make_index_sequence<Rows>{}) ...
            );
      }
  }

  template<typename T, std::size_t Rows, std::size_t Columns>
    constexpr bool square(const normal<T, Rows, Columns>& matrix){
      return Rows==Columns;
    }

  template<typename T, std::size_t Rows, std::size_t Columns>
    constexpr normal<T, Columns, Rows> transpose(const normal<T, Rows, Columns>& matrix){
      return impl::unpack<T, Columns, Rows>(
          impl::transpose_column_expand(matrix, std::make_index_sequence<Columns>{}),
          std::make_index_sequence<Rows*Columns>{}
          );
    }
}

#endif
