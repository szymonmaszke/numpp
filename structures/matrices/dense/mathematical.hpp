#ifndef NUMPP_STRUCTURES_MATRICES_DENSE_MATHEMATICAL_HPP_
#define NUMPP_STRUCTURES_MATRICES_DENSE_MATHEMATICAL_HPP_

#if defined  __GNUC__ && !defined __clang__
  #define CONSTEXPR constexpr
#elif
  #define CONSTEXPR
#endif


#include"./functions.hpp"

//POW FUNCTION
namespace numpp::matrix::impl{
  template<typename T, typename U, typename ReturnType, typename ArgumentFirst, typename ArgumentSecond,
    ReturnType (*Func)(ArgumentFirst&&, ArgumentSecond&&), std::size_t Rows, std::size_t Columns, std::size_t... Elements
  >
    CONSTEXPR auto propagate_function_two_arguments(
        ReturnType (*function)(ArgumentFirst&&, ArgumentSecond&&),
        const dense<T, Rows, Columns>& matrix,
        U&& arg,
        std::index_sequence<Elements...>
        ){
      return dense<T, Rows, Columns>{
        function(std::get<Elements>(matrix), std::forward<U>(exp)) ...
      };
    }

  template<typename T, typename U, typename ReturnType, typename ArgumentFirst,
    ReturnType (*Func)(ArgumentFirst&&), std::size_t Rows, std::size_t Columns, std::size_t... Elements
  >
    CONSTEXPR auto propagate_function_one_argument(
        ReturnType (*function)(ArgumentFirst&&),
        const dense<T, Rows, Columns>& matrix,
        std::index_sequence<Elements...>
        ){
      return dense<T, Rows, Columns>{
        function(std::get<Elements>(matrix)) ...
      };
    }
}

namespace std{
  template<typename T, typename U, std::size_t Rows, std::size_t Columns>
    CONSTEXPR numpp::matrix::dense<T, Rows, Columns> pow(
        const numpp::matrix::dense<T, Rows, Columns>& matrix,
        U&& exp
        ){
/**
  \ingroup numpp_structures_matrices_dense
  Standard library overload, matrix with element-wise power \f$A^exp\f$

  \param matrix Matrix whose elements will be taken to the exp power
  \exp power for every element
*/
      return numpp::matrix::impl::propagate_function_two_arguments<T, Rows, Columns>(
          std::pow,
          matrix, exp,
          std::make_index_sequence<Rows*Columns>{}
          );
    }

  template<typename T, std::size_t Rows, std::size_t Columns>
    CONSTEXPR numpp::matrix::dense<T, Rows, Columns> log(
        const numpp::matrix::dense<T, Rows, Columns>& matrix
        ){
/**
  \ingroup numpp_structures_matrices_dense
  Standard library overload, matrix element-wise logarithm \f$ln(A)\f$

  \param matrix Matrix whose elements will be logarithmized
*/
      return numpp::matrix::impl::propagate_function_one_argument<T, Rows, Columns>(
          std::log, matrix, std::make_index_sequence<Rows*Columns>{}
      );
    }

  template<typename T, std::size_t Rows, std::size_t Columns>
    CONSTEXPR numpp::matrix::dense<T, Rows, Columns> exp(
        const numpp::matrix::dense<T, Rows, Columns>& matrix
        ){
/**
  \ingroup numpp_structures_matrices_dense
  Standard library overload, matrix element-wise exp function \f$e^(A)\f$

  \param matrix Matrix whose elements will be exponentiated
*/
      return numpp::matrix::impl::propagate_function_one_argument<T, Rows, Columns>(
          std::exp, matrix, std::make_index_sequence<Rows*Columns>{}
      );
    }

  template<typename T, std::size_t Rows, std::size_t Columns>
    CONSTEXPR numpp::matrix::dense<T, Rows, Columns> abs(
        const numpp::matrix::dense<T, Rows, Columns>& matrix
        ){
/**
  \ingroup numpp_structures_matrices_dense
  Standard library overload, matrix element-wise abs function \f$|A|\f$

  \param matrix Matrix with exact same elements, but in absolute value
*/

      return numpp::matrix::impl::propagate_function_one_argument<T, Rows, Columns>(
          std::abs, matrix, std::make_index_sequence<Rows*Columns>{}
      );
    }
  template<typename T, std::size_t Rows, std::size_t Columns>
    CONSTEXPR numpp::matrix::dense<T, Rows, Columns> sqrt(
        const numpp::matrix::dense<T, Rows, Columns>& matrix
        ){
/**
  \ingroup numpp_structures_matrices_dense
  Standard library overload, matrix element-wise sqrt function \f$|A|\f$

  \param matrix Matrix with elements passed through sqrt standard library function
*/
      return numpp::matrix::impl::propagate_function_one_argument<T, Rows, Columns>(
          std::sqrt, matrix, std::make_index_sequence<Rows*Columns>{}
      );
    }

  template<typename T, std::size_t Rows, std::size_t Columns>
    CONSTEXPR numpp::matrix::dense<T, Rows, Columns> sin(
        const numpp::matrix::dense<T, Rows, Columns>& matrix
        ){
/**
  \ingroup numpp_structures_matrices_dense
  Standard library overload, matrix element-wise sin function \f$|A|\f$

  \param matrix Matrix with elements passed through sin standard library function
*/
      return numpp::matrix::impl::propagate_function_one_argument<T, Rows, Columns>(
          std::sin, matrix, std::make_index_sequence<Rows*Columns>{}
      );
    }

  template<typename T, std::size_t Rows, std::size_t Columns>
    CONSTEXPR numpp::matrix::dense<T, Rows, Columns> cos(
        const numpp::matrix::dense<T, Rows, Columns>& matrix
        ){
/**
  \ingroup numpp_structures_matrices_dense
  Standard library overload, matrix element-wise sin function \f$|A|\f$

  \param matrix Matrix with elements passed through cos standard library function
*/
      return numpp::matrix::impl::propagate_function_one_argument<T, Rows, Columns>(
          std::cos, matrix, std::make_index_sequence<Rows*Columns>{}
      );
    }
}

#endif
