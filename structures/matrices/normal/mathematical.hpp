#ifndef NUMPP_STRUCTURES_MATRICES_DENSE_MATHEMATICAL_HPP_
#define NUMPP_STRUCTURES_MATRICES_DENSE_MATHEMATICAL_HPP_

#if defined  __GNUC__ && !defined __clang__
  #define CONSTEXPR constexpr
#elif
  #define CONSTEXPR
#endif


#include"./normal_functions.hpp"

//POW FUNCTION
namespace numpp::matrix::impl{
  template<typename T, typename U, typename ReturnType, typename ArgumentFirst, typename ArgumentSecond,
    ReturnType (*Func)(ArgumentFirst&&, ArgumentSecond&&), std::size_t Rows, std::size_t Columns, std::size_t... Elements
  >
    CONSTEXPR auto propagate_function_two_arguments(
        ReturnType (*function)(ArgumentFirst&&, ArgumentSecond&&),
        const normal<T, Rows, Columns>& matrix,
        U&& arg,
        std::index_sequence<Elements...>
        ){
      return normal<T, Rows, Columns>{
        function(std::get<Elements>(matrix), std::forward<U>(exp)) ...
      };
    }

  template<typename T, typename U, typename ReturnType, typename ArgumentFirst,
    ReturnType (*Func)(ArgumentFirst&&), std::size_t Rows, std::size_t Columns, std::size_t... Elements
  >
    CONSTEXPR auto propagate_function_one_argument(
        ReturnType (*function)(ArgumentFirst&&),
        const normal<T, Rows, Columns>& matrix,
        std::index_sequence<Elements...>
        ){
      return normal<T, Rows, Columns>{
        function(std::get<Elements>(matrix)) ...
      };
    }
}

namespace std{
  template<typename T, typename U, std::size_t Rows, std::size_t Columns>
    CONSTEXPR numpp::matrix::normal<T, Rows, Columns> pow(
        const numpp::matrix::normal<T, Rows, Columns>& matrix,
        U&& exp
        ){
      return numpp::matrix::impl::propagate_function_two_arguments<T, Rows, Columns>(
          std::pow,
          matrix, exp,
          std::make_index_sequence<Rows*Columns>{}
          );
    }

  template<typename T, std::size_t Rows, std::size_t Columns>
    CONSTEXPR numpp::matrix::normal<T, Rows, Columns> log(
        const numpp::matrix::normal<T, Rows, Columns>& matrix
        ){
      return numpp::matrix::impl::propagate_function_one_argument<T, Rows, Columns>(
          std::log, matrix, std::make_index_sequence<Rows*Columns>{}
      );
    }

  template<typename T, std::size_t Rows, std::size_t Columns>
    CONSTEXPR numpp::matrix::normal<T, Rows, Columns> exp(
        const numpp::matrix::normal<T, Rows, Columns>& matrix
        ){
      return numpp::matrix::impl::propagate_function_one_argument<T, Rows, Columns>(
          std::exp, matrix, std::make_index_sequence<Rows*Columns>{}
      );
    }
  template<typename T, std::size_t Rows, std::size_t Columns>
    CONSTEXPR numpp::matrix::normal<T, Rows, Columns> abs(
        const numpp::matrix::normal<T, Rows, Columns>& matrix
        ){
      return numpp::matrix::impl::propagate_function_one_argument<T, Rows, Columns>(
          std::abs, matrix, std::make_index_sequence<Rows*Columns>{}
      );
    }
  template<typename T, std::size_t Rows, std::size_t Columns>
    CONSTEXPR numpp::matrix::normal<T, Rows, Columns> sqrt(
        const numpp::matrix::normal<T, Rows, Columns>& matrix
        ){
      return numpp::matrix::impl::propagate_function_one_argument<T, Rows, Columns>(
          std::sqrt, matrix, std::make_index_sequence<Rows*Columns>{}
      );
    }

  template<typename T, std::size_t Rows, std::size_t Columns>
    CONSTEXPR numpp::matrix::normal<T, Rows, Columns> sin(
        const numpp::matrix::normal<T, Rows, Columns>& matrix
        ){
      return numpp::matrix::impl::propagate_function_one_argument<T, Rows, Columns>(
          std::sin, matrix, std::make_index_sequence<Rows*Columns>{}
      );
    }

  template<typename T, std::size_t Rows, std::size_t Columns>
    CONSTEXPR numpp::matrix::normal<T, Rows, Columns> cos(
        const numpp::matrix::normal<T, Rows, Columns>& matrix
        ){
      return numpp::matrix::impl::propagate_function_one_argument<T, Rows, Columns>(
          std::cos, matrix, std::make_index_sequence<Rows*Columns>{}
      );
    }
}

#endif
