#ifndef MATRICES_SPARSE_BLOCK_HPP_
#define MATRICES_SPARSE_BLOCK_HPP_

#include<vector>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<algorithm>
#include<array>

#include"../../vector/vector_utils.hpp"


namespace numpp::matrix{
  struct sparse_block{};

  template<typename T, std::size_t Rows, std::size_t Columns,
    std::size_t Elements=static_cast<std::size_t>(Rows*Columns)/8,
    std::size_t Alignment=64
      >
      //VERSION WITH MAXIMUM POSSIBLE CACHE HIT
      //ANALYZE BLOCK STRUCTURE WHERE THIS STYLE IS PREFFERED
      class sparse{
        public:
          using value_type = T;
          using size_type = std::size_t;
          using reference = T&;
          using const_reference = const T&;
          using pointer = T*;
          using const_pointer = const T*;

          using type = sparse_block;

          sparse()=default;
          sparse(const sparse&)=default;
          sparse(sparse&&)=default;
          sparse& operator=(const sparse&)=default;
          sparse& operator=(sparse&&)=default;

          sparse(std::initializer_list<std::initializer_list<T>> elements){
            size_t i = 0;
            matrix.reserve(Elements);
            size_t row_index=0;

            for(const auto& row: elements){
              size_t elements_counter = 0;
              bool chain = false;

              for(const auto& element: row){
                if(element!=0){
                  if(chain)
                    matrix.emplace_back(element);
                  else{
                    matrix.emplace_back(0);
                    matrix.emplace_back(elements_counter);
                    matrix.emplace_back(element);
                    chain = true;
                  }
                }
                else if(chain)
                  chain = false;
                ++elements_counter;
              }

              rows[row_index++] = matrix.size();
            }
          }

          size_type size() const noexcept{
            return matrix.size();
          }

          const std::vector<T>& data() const noexcept{
            return matrix;
          }

          std::vector<T>& data() noexcept{
            return matrix;
          }

          template<typename U>
            auto operator*(const numpp::vector<U,Columns, false>& vec){
              vector<U,Rows,false> output{};

              #pragma omp for schedule(simd:dynamic)
              for(int i=0; i<(rows.size()-1); ++i){

                for(size_t j=rows[i], mat_size=rows[i+1]; j<mat_size; ++j){
                  size_t col = static_cast<size_t>(matrix[j]) % Columns;

                  while(matrix[++j]!=0){

                    output(i) += matrix[j]*vec(col);
                    ++col;

                  }
                }
              }
              return output;
            }


        private:
          alignas(Alignment) std::vector<T> matrix{};
          alignas(Alignment) std::array<size_t, Rows> rows{};
      };
}

#endif
