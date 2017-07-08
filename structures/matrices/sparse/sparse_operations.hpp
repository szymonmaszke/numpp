#ifndef NUMPP_MATRICES_SPARSE_OPERATIONS_HPP_
#define NUMPP_MATRICES_SPARSE_OPERATIONS_HPP_

#include"sparse_structure.hpp"
#include"../../vector/vector_utils.hpp"
#include<future>

namespace numpp::mat{
  namespace impl{
    template<typename T, typename U, std::size_t Rows, std::size_t Columns>
      U multiply(
          const std::vector<T>& matrix_block,
          const vector<U, Columns, false>& vector
          ){
        U element{};
        for(size_t i=0; i<matrix_block.size(); ++i){
          size_t col = matrix_block[i] % Columns;
          while(matrix_block[++i]!=0){
            element+=matrix_block[i]*vector(col);
            ++col;
          }
        }
        return element;
      }

  }

  //CHECK FOR TYPE COMPLIANCE T AND U!
  template<typename T, typename U, std::size_t Rows, std::size_t Columns>
    auto operator*(
        const matrix::sparse<T, Rows, Columns>& mat,
        const vector<U,Columns, false>& vec
        ){
      vector<U,Columns,false> result{};
      for(size_t i=0; i<Columns-1; ++i){
        //ZNAJDŹ DOBRY SPOSÓB NA PARALELIZM
      }
    }

}

#endif
