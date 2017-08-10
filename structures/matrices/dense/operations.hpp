#ifndef NUMPP_STRUCTURES_MATRICES_DENSE_OPERATIONS_HPP_
#define NUMPP_STRUCTURES_MATRICES_DENSE_OPERATIONS_HPP_

#include"utils.hpp"
#include<tuple>

namespace numpp::matrix{
  //IMPLEMENTATION DETAILS
  namespace impl{
    template<typename T, typename U, std::size_t RowsColumns, std::size_t Rows, std::size_t Columns, std::size_t... Index>
      constexpr auto element_wise(
          const dense<T,Rows,RowsColumns>& first,
          const dense<U,RowsColumns,Columns>& second,
          std::size_t row,
          std::size_t col,
          std::index_sequence<Index...>
          ){
        return ((first(row, Index) * second(Index, col)) + ... );
      }

    template<typename T, typename U, std::size_t RowsColumns, std::size_t Rows, std::size_t Columns, std::size_t... Index>
      constexpr auto column_wise(
          const dense<T,Rows,RowsColumns>& first,
          const dense<U,RowsColumns,Columns>& second,
          std::size_t row,
          std::index_sequence<Index...>
          ){
        return std::make_tuple(
            (element_wise(first, second, row, Index, std::make_index_sequence<RowsColumns>{}))...
            );
      }

    template<typename T, typename U, std::size_t RowsColumns, std::size_t Rows, std::size_t Columns, std::size_t... Index>
      constexpr auto row_wise(
          const dense<T,Rows,RowsColumns>& first,
          const dense<U,RowsColumns,Columns>& second,
          std::index_sequence<Index...>
          ){
        return std::tuple_cat(
            column_wise(first, second, Index, std::make_index_sequence<Columns>{})...
         );
      }

    template<typename T, size_t Rows, std::size_t Columns, typename Tuple, std::size_t... Elements>
      constexpr auto unpack(Tuple&& tup, std::index_sequence<Elements...>){
        return matrix::dense<T, Rows, Columns>{
          std::get<Elements>(tup) ...
        };
      }

    template<typename T, typename U, std::size_t Rows, std::size_t Columns, typename Operation, std::size_t... Index>
      constexpr auto accumulate(
          const dense<T,Rows,Columns>& first,
          const dense<U,Rows,Columns>& second,
          Operation&& op,
          std::index_sequence<Index...>
          ){
        return dense<std::common_type_t<T,U>, Rows, Columns>{
          op(get<Index>(first), get<Index>(second)) ...
        };
      }

    template<typename T, typename U, std::size_t Rows, std::size_t Columns, typename Operation, std::size_t... Index>
      constexpr auto accumulate(
          const dense<T,Rows,Columns>& first,
          const U scalar,
          Operation&& op,
          std::index_sequence<Index...>
          ){
        return dense<std::common_type_t<T,U>, Rows, Columns>{
          op(get<Index>(first), scalar) ...
        };
      }
  }
  //END OF IMPLEMENTATION DETAILS

  template<typename T, typename U, std::size_t Rows, std::size_t Columns>
    constexpr auto operator+(
        const dense<T, Rows, Columns>& first,
        const dense<U, Rows, Columns>& second
        ){
/**
  \ingroup numpp_structures_matrices_dense
  Element-wise addition of two matrices of the same size

*/
      return impl::accumulate(first, second, std::plus<>{},
          std::make_index_sequence<Rows*Columns>{});
    }

  template<typename T, typename U, std::size_t Rows, std::size_t Columns>
    constexpr auto operator-(
        const dense<T, Rows, Columns>& first,
        const dense<U, Rows, Columns>& second
        ){
/**
  \ingroup numpp_structures_matrices_dense
  Element-wise subtraction of two matrices of the same size

*/
      return impl::accumulate(first, second, std::minus<>{},
          std::make_index_sequence<Rows*Columns>{});
    }

  template<typename T, typename U, std::size_t RowsColumns, std::size_t Rows, std::size_t Columns>
    constexpr auto operator*(
        const dense<U, Rows, RowsColumns>& first,
        const dense<T, RowsColumns, Columns>& second
        ){
/**
  \ingroup numpp_structures_matrices_dense
  Matrix row-column multiplication

  \returns Matrix with appropriate size after multiplication (dense<common_type_t<U,T>, Rows, Columns>)

*/
      return impl::unpack<std::common_type_t<T,U>, Rows, Columns>(
          impl::row_wise(first, second, std::make_index_sequence<Rows>{}),
          std::make_index_sequence<Rows*Columns>{}
      );
    }

  //ELEMENT-WISE MULTIPLICATION
  template<typename T, typename U, std::size_t Rows, std::size_t Columns>
    constexpr auto multiply(
        const dense<T,Rows,Columns>& first,
        const dense<U,Rows,Columns>& second
        ){
/**
  \ingroup numpp_structures_matrices_dense
  Element-wise multiplication of two matrices of the same size

*/
      return impl::accumulate(first, second, std::multiplies<>{},
          std::make_index_sequence<Rows*Columns>{});
    }


  template<typename T,typename U,std::size_t Rows,std::size_t Columns>
    constexpr auto operator*(
        const dense<T,Rows,Columns>& matrix,
        const U scalar
        ){
/**
  \ingroup numpp_structures_matrices_dense
  Multiplication of dense matrix and scalar

*/
      return impl::accumulate(matrix, scalar, std::multiplies<>{},
          std::make_index_sequence<Rows*Columns>{});
    }


  template<typename T, typename U, std::size_t Rows,std::size_t Columns>
    constexpr auto operator*(
        const U scalar,
        const dense<T,Rows,Columns>& matrix
        ){
/**
  \ingroup numpp_structures_matrices_dense
  Multiplication of dense matrix and scalar

*/

      return matrix*scalar;
    }

  template<typename T, typename U, std::size_t Rows, std::size_t Columns>
    constexpr auto operator/(
        const dense<T,Rows,Columns>& matrix,
        const U scalar
        ){
/**
  \ingroup numpp_structures_matrices_dense
  Element-wise division of matrix against scalar

*/
      return impl::accumulate(matrix, scalar, std::divides<>{},
          std::make_index_sequence<Rows*Columns>{});
    }

  template<typename T, typename U, std::size_t Rows, std::size_t Columns>
    constexpr auto operator/(
        const dense<T,Rows,Columns>& first,
        const dense<U,Rows,Columns>& second
        ){
/**
  \ingroup numpp_structures_matrices_dense
  Element-wise division of two matrices

*/
      return impl::accumulate(first, second, std::divides<>{},
          std::make_index_sequence<Rows*Columns>{});
    }
}


#endif
