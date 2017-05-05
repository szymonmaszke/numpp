#ifndef MATRIX_NORMAL_OPERATIONS_HPP
#define MATRIX_NORMAL_OPERATIONS_HPP

#include"normal_utils.hpp"
#include"tuple"

namespace numpp::matrix{
  //IMPLEMENTATION DETAILS
  namespace impl{
    template<typename T, typename U, std::size_t RowsColumns, std::size_t Rows, std::size_t Columns, std::size_t... Index>
      constexpr auto element_wise(
          const normal<T,Rows,RowsColumns>& first,
          const normal<U,RowsColumns,Columns>& second,
          std::size_t row,
          std::size_t col,
          std::index_sequence<Index...>
          ){
        return ((first(row, Index) * second(Index, col)) + ... );
      }

    template<typename T, typename U, std::size_t RowsColumns, std::size_t Rows, std::size_t Columns, std::size_t... Index>
      constexpr auto column_wise(
          const normal<T,Rows,RowsColumns>& first,
          const normal<U,RowsColumns,Columns>& second,
          std::size_t row,
          std::index_sequence<Index...>
          ){
        return std::make_tuple(
            (element_wise(first, second, row, Index, std::make_index_sequence<RowsColumns>{}))...
            );
      }

    template<typename T, typename U, std::size_t RowsColumns, std::size_t Rows, std::size_t Columns, std::size_t... Index>
      constexpr auto row_wise(
          const normal<T,Rows,RowsColumns>& first,
          const normal<U,RowsColumns,Columns>& second,
          std::index_sequence<Index...>
          ){
        return std::tuple_cat(
            column_wise(first, second, Index, std::make_index_sequence<Columns>{})...
         );
      }

    template<typename T, size_t Rows, std::size_t Columns, typename Tuple, std::size_t... Elements>
      constexpr auto unpack(Tuple&& tup, std::index_sequence<Elements...>){
        return matrix::normal<T, Rows, Columns>{
          std::get<Elements>(tup) ...
        };
      }

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
  //END OF IMPLEMENTATION DETAILS

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

  template<typename T, typename U, std::size_t RowsColumns, std::size_t Rows, std::size_t Columns>
    constexpr auto operator*(
        const normal<U, Rows, RowsColumns>& first,
        const normal<T, RowsColumns, Columns>& second
        ){
      return impl::unpack<std::common_type_t<T,U>, Rows, Columns>(
          impl::row_wise(first, second, std::make_index_sequence<Rows>{}),
          std::make_index_sequence<Rows*Columns>{}
      );
    }

  //ELEMENT-WISE MULTIPLICATION
  template<typename T, typename U, std::size_t Rows, std::size_t Columns>
    constexpr auto multiply(
        const normal<T,Rows,Columns>& first,
        const normal<U,Rows,Columns>& second
        ){
      return impl::accumulate(first, second, std::multiplies<>{},
          std::make_index_sequence<Rows*Columns>{});
    }


  template<typename T,typename U,std::size_t Rows,std::size_t Columns>
    constexpr auto operator*(
        const normal<T,Rows,Columns>& matrix,
        const U scalar
        ){
      return impl::accumulate(matrix, scalar, std::multiplies<>{},
          std::make_index_sequence<Rows*Columns>{});
    }


  template<typename T, typename U, std::size_t Rows,std::size_t Columns>
    constexpr auto operator*(
        const U scalar,
        const normal<T,Rows,Columns>& matrix
        ){
      return matrix*scalar;
    }

  template<typename T, typename U, std::size_t Rows, std::size_t Columns>
    constexpr auto operator/(
        const normal<T,Rows,Columns>& matrix,
        const U scalar
        ){
      return impl::accumulate(matrix, scalar, std::divides<>{},
          std::make_index_sequence<Rows*Columns>{});
    }

  template<typename T, typename U, std::size_t Rows, std::size_t Columns>
    constexpr auto operator/(
        const normal<T,Rows,Columns>& first,
        const normal<U,Rows,Columns>& second
        ){
      return impl::accumulate(first, second, std::divides<>{},
          std::make_index_sequence<Rows*Columns>{});
    }
}


#endif
