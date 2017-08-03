#ifndef NUMPP_STRUCTURES_MATRICES_SPARSE_BLOCK_HPP_
#define NUMPP_STRUCTURES_MATRICES_SPARSE_BLOCK_HPP_

#include<vector>

#include"../../vector/vector_utils.hpp"

namespace numpp::matrix::sparse{
  template<typename T, std::size_t Rows, std::size_t Columns>
      //VERSION WITH MAXIMUM POSSIBLE CACHE HIT
      //ANALYZE BLOCK STRUCTURE WHERE THIS STYLE IS PREFFERED
      class block{
        public:
          using value_type = T;
          using size_type = std::size_t;
          using reference = T&;
          using const_reference = const T&;
          using pointer = T*;
          using const_pointer = const T*;

          block()=default;
          block(const block&)=default;
          block(block&&)=default;
          block& operator=(block&&)=default;
          block& operator=(const block&)=default;

          block(std::initializer_list<std::initializer_list<T>> elements){

            for(auto row=std::begin(elements); row!=std::end(elements); ++row){
             const auto iterator_position{std::distance(std::begin(elements), row)};
              std::size_t elements_counter = 0;
              bool chain = false;

              auto col=std::begin(*row);
              //FIND FIRST NON-ZERO ELEMENT
              for(; col!=std::end(*row); ++col){
                if(*col != 0){
                  matrix[iterator_position].emplace_back(elements_counter);
                  matrix[iterator_position].emplace_back(*col);
                  chain=true;
                  ++col; ++elements_counter;
                  break;
                }
                ++elements_counter;
              }

              //CHAIN OTHER NON-ZERO ELEMENTS
              for(; col!=std::end(*row); ++col){
                if(*col!=0){
                  if(chain)
                    matrix[iterator_position].emplace_back(*col);
                  else{
                    matrix[iterator_position].emplace_back(0);
                    matrix[iterator_position].emplace_back(elements_counter);
                    matrix[iterator_position].emplace_back(*col);
                    chain = true;
                  }
                }
                else if(chain)
                  chain = false;
                ++elements_counter;
              }
            }
          }

          size_type size() const noexcept{
            return matrix.size();
          }

          const std::array<std::vector<T>, Rows>& data() const noexcept{
            return matrix;
          }

          std::array<std::vector<T>, Rows>&  data() noexcept{
            return matrix;
          }

          template<typename U>
            auto operator*(const numpp::vector<U,Columns, false>& vec){
              vector<U,Rows,false> output{};

              #pragma omp for schedule(simd:dynamic)
              for(std::size_t row=0; row<Rows; ++row){

                for(std::size_t col=0; col<matrix[row].size(); ++col){
                  std::size_t col_index = static_cast<std::size_t>(matrix[row][col]);
                  while(matrix[row][++col]!=0){
                    output(row) += matrix[row][col]*vec(col_index);
                    ++col_index;
                  }
                }
              }
              return output;
            }

        private:
          std::array<std::vector<T>, Rows> matrix{};
      };
}

#endif
