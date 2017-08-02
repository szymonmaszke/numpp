#ifndef NUMPP_STRUCTURES_VECTOR_FUNCTIONS_HPP_
#define NUMPP_STRUCTURES_VECTOR_FUNCTIONS_HPP_

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


#if defined  __GNUC__ && !defined __clang__
  #define CONSTEXPR constexpr
#elif
  #define CONSTEXPR
#endif

  namespace norm{
    template<typename T, std::size_t Size, bool Transposition>
      CONSTEXPR T euclidean(const vector<T, Size, Transposition>& vec){
        return std::sqrt(sum(vec));
      }
    template<typename T, std::size_t Size, bool Transposition>
      CONSTEXPR T max(const vector<T, Size, Transposition>& vec){
        T ret{std::abs(vec[0])};
        for(std::size_t i=1; i<Size; ++i)
          if(std::abs(vec[i])>ret)
            ret = vec[i];
        return ret;
      }

    template<typename T, std::size_t Size, bool Transposition>
      CONSTEXPR T taxicab(const vector<T, Size, Transposition>& vec){
        T ret{};
        for(std::size_t i=0; i<Size; ++i)
          ret += std::abs(vec[i]);
        return ret;
      }
  }
}

#endif
