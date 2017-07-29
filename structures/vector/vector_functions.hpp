#ifndef NUMPP_VECTOR_FUNCTIONS_HPP_
#define NUMPP_VECTOR_FUNCTIONS_HPP_

#include"vector_operations.hpp"

namespace numpp{
  template<typename T, std::size_t Size, bool Transposition>
    constexpr auto transpose(vector<T, Size, Transposition> vec){
      return vector<T, Size, !Transposition>{vec};
    }


}

#endif
