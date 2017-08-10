#ifndef NUMPP_STRUCTURES_VECTOR_OPERATIONS_HPP_
#define NUMPP_STRUCTURES_VECTOR_OPERATIONS_HPP_

#include"utils.hpp"
#include"../matrices/dense/functions.hpp"

namespace numpp{
  namespace impl{
      template<typename T, typename... Args>
        constexpr auto multiply(const T& first_elem, const Args&... second){
          return std::make_tuple((first_elem * second)...);
        }

      template<typename T, std::size_t Rows, std::size_t Columns, typename Tuple, std::size_t... Elements>
        constexpr auto unpack(Tuple&& tup, std::index_sequence<Elements...>){
          return matrix::dense<T, Rows, Columns>{
            std::get<Elements>(tup) ...
          };
      }

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
          T&& scalar,
          const vector<U,Size,Transposition>& vec,
          Operation&& op,
          std::index_sequence<Index...>
      ){
        return numpp::vector<std::common_type_t<T,U>, Size, Transposition>{
          op(vec(Index), scalar) ...
        };
    }

    template<typename T, typename U, std::size_t FirstSize, std::size_t SecondSize, typename Operation, std::size_t... Rows, std::size_t... Columns>
      constexpr auto accumulate(
          const vector<T,FirstSize,false>& first,
          const vector<U,SecondSize,true>& second,
          Operation&& op,
          std::index_sequence<Rows...>,
          std::index_sequence<Columns...>
      ){
        return unpack<std::common_type_t<T,U>, FirstSize, SecondSize>(
            std::tuple_cat(multiply(first(Rows), second(Columns)...)...),
            std::make_index_sequence<FirstSize*SecondSize>{}
            );
      }
  }
  //END OF IMPLEMENTATION DETAILS

	template<typename T, typename U, std::size_t Size, bool Transposition>
		constexpr auto operator+(
				const vector<T,Size,Transposition>& first,
				const vector<U,Size,Transposition>& second
		){
/**
  \ingroup numpp_structures_vector
  \brief returns the sum of two vectors \f$first+second\f$ which is a new vector object
*/
      return impl::accumulate(first, second, std::plus<>{},
          std::make_index_sequence<Size>{});
		}

	template<typename T, typename U, std::size_t Size, bool Transposition>
		constexpr auto operator-(
				const vector<T,Size,Transposition>& first,
				const vector<U,Size,Transposition>& second
		){
/**
  \ingroup numpp_structures_vector
  \brief returns the subtraction of two vectors \f$first-second\f$ which is a new vector object
*/
      return impl::accumulate(first, second, std::minus<>{},
          std::make_index_sequence<Size>{});
		}


	template<typename T, typename U, std::size_t Size, bool Transposition>
		constexpr auto operator*(
				const vector<T,Size,Transposition>& vec,
				U&& scalar
		){
/**
  \ingroup numpp_structures_vector
  \brief returns the multiplication of vector with scalar\f$vec*scalar\f$ which is a new vector object
*/
      return impl::accumulate(std::forward<U>(scalar), vec, std::multiplies<>{},
          std::make_index_sequence<Size>{});
		}


	template<typename T,typename U, std::size_t Size, bool Transposition>
		constexpr auto operator*(
				U scalar,
				const vector<T,Size,Transposition>& vec
		){
/**
  \ingroup numpp_structures_vector
  \brief returns the multiplication of scalar and vector \f$scalar*vec\f$ which is a new vector object
*/
      return vec*scalar;
		}

	template<typename T,typename U, std::size_t Size>
		constexpr std::common_type_t<T,U> operator*(
				const vector<T, Size, true>& first,
				const vector<U, Size, false>& second
		){
/**
  \ingroup numpp_structures_vector
  \brief returns the multiplication of the form \f$first^T*second\f$
  \returns common type of two vectors data type, e.g. double for float and double types
*/
      std::common_type_t<T,U> ret{};
      for(std::size_t i=0; i<Size; ++i)
        ret += first(i)*second(i);
      return ret;
		}

	template<typename T,typename U, std::size_t Rows, std::size_t Columns>
		constexpr auto operator*(
				const vector<T, Rows, false>& first,
				const vector<U, Columns, true>& second
		){
/**
  \ingroup numpp_structures_vector
  \brief returns the multiplication of the form \f$first*second^T\f$
  \returns Matrix with data type common_type and size Rows and Columns
*/
      return impl::accumulate(first, second, std::multiplies<>{},
          std::make_index_sequence<Rows>{}, std::make_index_sequence<Columns>{}
      );
		}

	template<typename T, typename U, std::size_t Size, bool Transposition>
		constexpr auto operator/(
				const vector<T,Size,Transposition>& vec,
				U scalar
		){
/**
  \ingroup numpp_structures_vector
  \brief returns the division of vector with scalar of the form \f$\frac{1}{scalar}*vec \f$
  \returns vector divided by scalar
*/
      return impl::accumulate(scalar, vec, std::divides<>{},
          std::make_index_sequence<Size>{});
		}
}

#endif
