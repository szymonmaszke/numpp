#ifndef NUMPP_STRUCTURES_MATRICES_DENSE_UTILS_HPP_
#define NUMPP_STRUCTURES_MATRICES_DENSE_UTILS_HPP_

#include"structure.hpp"

namespace numpp::matrix{
  template<std::size_t Index, typename T, std::size_t Rows, std::size_t Columns>
      constexpr T& get(dense<T, Rows, Columns>& n){
/**
  \ingroup numpp_structures_matrices_dense
  \brief Overload standard operator get for dense matrix

  Elements are taken column-wise.
  <b>Example:</b>
  \code
  numpp::matrix::dense<int, 2, 2> foo{1,2,
                                      3,4};
  std::cout << get<0>(foo) << std::endl; //Returns 1
  std::cout << get<2>(foo) << std::endl; //Returns 3, jumps to the next column
  \endcode

  \returns Element of matrix
*/
        constexpr std::size_t row = static_cast<std::size_t>(Index/(Columns));
        constexpr std::size_t col= Index%Columns;
        return n(row, col);
      }

  template<std::size_t Index, typename T, std::size_t Rows, std::size_t Columns>
      constexpr T& get(dense<T, Rows, Columns>&& n){
/**
  \ingroup numpp_structures_matrices_dense
  \overload
*/
        constexpr std::size_t row = static_cast<std::size_t>(Index/(Columns));
        constexpr std::size_t col= Index%Columns;
        return std::move(n(row,col));

      }

  template<std::size_t Index, typename T, std::size_t Rows, std::size_t Columns>
      constexpr const T& get(const dense<T, Rows, Columns>& n){
/**
  \ingroup numpp_structures_matrices_dense
  \overload
*/
        constexpr std::size_t row = static_cast<std::size_t>(Index/(Columns));
        constexpr std::size_t col= Index%Columns;
        return n(row, col);
      }

  template<std::size_t Index, typename T, std::size_t Rows, std::size_t Columns>
      constexpr const T&& get(const dense<T, Rows, Columns>&& n){
/**
  \ingroup numpp_structures_matrices_dense
  \overload
*/
        constexpr std::size_t row = static_cast<std::size_t>(Index/(Columns));
        constexpr std::size_t col= Index%Columns;
        return std::move(n(row,col));
      }
}


namespace std {
/**
\ingroup numpp_structures_matrices_dense

\class tuple_size

\tparam T arithmetic type contained in matrix class
\tparam Rows number of matrix rows
\tparam Columns number of matrix columns

\brief tuple_size specialization for numpp::matrix::dense

Check C++ standard library for information about this structure.

*/
  template<typename T, std::size_t Rows, std::size_t Columns>
    class tuple_size<numpp::matrix::dense<T,Rows,Columns>> :
    public integral_constant<std::size_t, Rows*Columns>
      {};

/**
\ingroup numpp_structures_matrices_dense

\class tuple_element

\tparam Index Index inside the vector container, specifying concrete element
\tparam T arithmetic type contained in matrix class
\tparam Rows number of matrix rows
\tparam Columns number of matrix columns

\brief tuple_element specialization for numpp::matrix::dense

Check C++ standard library for information about this structure.

*/

  template<std::size_t Index, typename T, std::size_t Rows, std::size_t Columns>
    class tuple_element<Index, numpp::matrix::dense<T,Rows,Columns>>
    {
      public:
        using type = T;
    };
}

#endif
