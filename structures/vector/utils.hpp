#ifndef NUMPP_STRUCTURES_VECTOR_UTILS_HPP_
#define NUMPP_STRUCTURES_VECTOR_UTILS_HPP_

#include"structure.hpp"

namespace numpp{
  template<std::size_t Index, typename T, std::size_t Size, bool Transposition>
      constexpr T& get(numpp::vector<T, Size, Transposition>& v){
/**
  \ingroup numpp_structures_vector
  \brief Overload standard operator get for vector
  \returns Element of vector of passed index
*/
        return std::get<Index>(v.vector_);
      }

  template<std::size_t Index, typename T, std::size_t Size, bool Transposition>
      constexpr T&& get(numpp::vector<T, Size, Transposition>&& v){
/**
  \ingroup numpp_structures_vector
  \overload
*/
        return std::get<Index>(std::move(v.vector_));
      }

  template<std::size_t Index, typename T, std::size_t Size, bool Transposition>
      constexpr const T& get(const numpp::vector<T, Size, Transposition>& v){
/**
  \ingroup numpp_structures_vector
  \overload
*/
        return std::get<Index>(v.vector_);
      }

  template<std::size_t Index, typename T, std::size_t Size, bool Transposition>
      constexpr const T&& get(const numpp::vector<T, Size, Transposition>&& v){
/**
  \ingroup numpp_structures_vector
  \overload
*/
        return std::get<Index>(std::move(v.vector_));
      }
}


namespace std {
/**
\ingroup numpp_structures_vector

\class tuple_size

\tparam T arithmetic type contained in vector class
\tparam Size size of the vector
\tparam Transposition bool indicating whether the vector is transposed

\brief tuple_size specialization for numpp::vector

Check C++ standard library for information about this structure.

*/
  template<typename T, std::size_t Size, bool Tranposition>
    class tuple_size<numpp::vector<T,Size,Tranposition> > :
    public integral_constant<std::size_t, Size>{
    };

/**
\ingroup numpp_structures_vector

\class tuple_element

\tparam Index Index inside the vector container, specifying concrete element
\tparam T arithmetic type contained in vector class
\tparam Size size of the vector
\tparam Transposition bool indicating whether the vector is transposed

\brief tuple_element specialization for numpp::vector

Check C++ standard library for information about this structure.

*/

  template<std::size_t Index, typename T, std::size_t Size, bool Transposition>
    class tuple_element<Index, numpp::vector<T,Size,Transposition>>{
      public:
        using type = T;
    };
}

#endif
