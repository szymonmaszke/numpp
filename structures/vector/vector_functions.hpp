#ifndef NUMPP_VECTOR_FUNCTIONS_HPP_
#define NUMPP_VECTOR_FUNCTIONS_HPP_

#include"vector_operations.hpp"

namespace numpp{
  template<typename T, std::size_t Size, bool Transposition>
    constexpr auto transpose(vector<T, Size, Transposition> vec){
      return vector<T, Size, !Transposition>{vec};
    }

  template<typename T, typename U, std::size_t Size, bool TranspositionOne, bool TranspositionTwo>
    constexpr std::common_type_t<T,U> sum(
        const vector<T, Size, TranspositionOne>& first,
        const vector<U, Size, TranspositionTwo>& second
    ){
      std::common_type_t<T,U> ret{};
      for(std::size_t i=0; i<Size; ++i)
        ret += first(i)*second(i);
      return ret;
    }

  template<typename T, std::size_t Size, bool Transposition>
    constexpr T sum(const vector<T, Size, Transposition>& vec){
      T ret{};
      for(std::size_t i=0; i<Size; ++i)
        ret += vec(i)*vec(i);
      return ret;
    }
}

#endif
