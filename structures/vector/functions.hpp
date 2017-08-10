#ifndef NUMPP_STRUCTURES_VECTOR_FUNCTIONS_HPP_
#define NUMPP_STRUCTURES_VECTOR_FUNCTIONS_HPP_

#include"operations.hpp"

namespace numpp{
  template<typename T, std::size_t Size, bool Transposition>
    constexpr auto transpose(vector<T, Size, Transposition> vec){
/**
  \ingroup numpp_structures_vector
  \brief returns transposed vector
*/
      return vector<T, Size, !Transposition>{vec};
    }

  template<typename T, typename U, std::size_t Size, bool TranspositionOne, bool TranspositionTwo>
    constexpr std::common_type_t<T,U> sum(
        const vector<T, Size, TranspositionOne>& first,
        const vector<U, Size, TranspositionTwo>& second
    ){
/**
  \ingroup numpp_structures_vector
  \brief returns result of the operation \f$first^T * second \f$ without performing pointless transposition

  You are advised to use this version, not explicit transposition of vector
*/
      std::common_type_t<T,U> ret{};
      for(std::size_t i=0; i<Size; ++i)
        ret += first(i)*second(i);
      return ret;
    }

  template<typename T, std::size_t Size, bool Transposition>
    constexpr T sum(const vector<T, Size, Transposition>& vec){
/**
  \ingroup numpp_structures_vector
  \brief returns result of the operation \f$vec^T * vec\f$ without performing pointless transposition

  You are advised to use this version, not explicit transposition of vector
*/
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
/**
  \ingroup numpp_structures_vector
  \brief returns Euclidean (\f$ l^2 \f$) norm of the vector
*/
        return std::sqrt(sum(vec));
      }
    template<typename T, std::size_t Size, bool Transposition>
      CONSTEXPR T max(const vector<T, Size, Transposition>& vec){
/**
  \ingroup numpp_structures_vector
  \brief returns maximum norm of the vector which has the form: \f$ ||x|| = \max(|x_1|) \f$
*/
        T ret{std::abs(vec[0])};
        for(std::size_t i=1; i<Size; ++i)
          if(std::abs(vec[i])>ret)
            ret = vec[i];
        return ret;
      }

    template<typename T, std::size_t Size, bool Transposition>
      CONSTEXPR T taxicab(const vector<T, Size, Transposition>& vec){
/**
  \ingroup numpp_structures_vector
  \brief returns Taxicab/Mahattan norm of the vector
*/
        T ret{};
        for(std::size_t i=0; i<Size; ++i)
          ret += std::abs(vec[i]);
        return ret;
      }
  }
}

#endif
