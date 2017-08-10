#ifndef NORMAL_VECTOR_OPERATIONS_HPP
#define NORMAL_VECTOR_OPERATIONS_HPP

#include"../vector.hpp"

namespace numpp{
  namespace impl{
    template<typename T, typename U, std::size_t Rows, std::size_t Columns, std::size_t... Index>
      constexpr auto multiply(
          const matrix::dense<T,Rows,Columns>& mat,
          const vector<U,Columns, false>& vec,
          std::size_t row,
          std::index_sequence<Index...>
          ){
        return ((mat(row, Index) * vec(Index)) + ... );
      }

    template<typename T, typename U, size_t Rows, std::size_t Columns, std::size_t... Elements>
      constexpr auto make_vector(
          const matrix::dense<T, Rows, Columns>& mat,
          const vector<U,Columns, false>& vec,
          std::index_sequence<Elements...>
          ){
        return vector<std::common_type_t<T,U>, Rows, false>{
          multiply(mat, vec, Elements, std::make_index_sequence<Columns>{}) ...
        };
      }
  }

  template<typename T, typename U, std::size_t Rows, std::size_t Columns>
    constexpr auto operator*(
        const matrix::dense<T, Rows, Columns>& mat,
        const vector<U,Columns, false>& vec
        ){
/**
  \ingroup numpp_structures_vector
  \brief returns the result of \f$mat*vec\f$ which is a new vector object
*/
      return impl::make_vector(mat, vec, std::make_index_sequence<Rows>{});
    }
}

#endif
