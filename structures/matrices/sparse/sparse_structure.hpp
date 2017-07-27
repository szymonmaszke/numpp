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
  template<typename T>
    struct block{
      public:
        std::vector<T> data;
        std::size_t column;
    };
  //BLOCK OF CONTIGUOUS DATA IN MATRIX

  template<typename T, std::size_t Rows, std::size_t Columns>
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
          sparse& operator=(sparse&&)=default;
          sparse& operator=(const sparse&)=default;

          sparse(std::initializer_list<std::initializer_list<T>> elements){

            /* for(auto row=std::begin(elements); row!=std::end(elements); ++row){ */
            /*   std::size_t elements_counter = 0; */
            /*   const auto iterator_position{std::distance(std::begin(elements), row)}; */

            /*   for(auto col=row->begin(), end=row->end(); col!=end; ++col){ */
            /*     if(*col != 0){ */
            /*       numpp::matrix::block<T> chain{}; */
            /*       chain.column = elements_counter; */

            /*       while((*col != 0) && (col!=end)){ */
            /*         chain.data.push_back(*col); */
            /*         ++elements_counter; */
            /*         ++col; */
            /*       } */
            /*       matrix[iterator_position].emplace_back(chain); */
            /*     } */
            /*     ++elements_counter; */
            /*   } */
            /* } */
          /* } */

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

          const std::array<std::vector<block<T>>, Rows>& data() const noexcept{
            return matrix;
          }

          std::array<std::vector<block<T>>, Rows>& data() noexcept{
            return matrix;
          }

          template<typename U>
            auto operator*(const numpp::vector<U,Columns, false>& vec){
              vector<U,Rows,false> output{};

              #pragma omp for schedule(simd:dynamic)
              for(std::size_t row=0; row<Rows; ++row){

                /* for(std::size_t block=0, block_end=matrix[row].size(); block<block_end; ++block){ */

                /*   const std::size_t col=matrix[row][block].column; */
                /*   const std::size_t element_end=matrix[row][block].data.size(); */
                /*   #pragma omp simd */
                /*   for(std::size_t element=0; element<element_end; ++element){ */
                /*     output(row) += matrix[row][block].data[element]*vec(col+element); */
                /*   } */
                /* } */

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
          /* std::array<std::vector<block<T>>, Rows> matrix{}; */
          std::array<std::vector<T>, Rows> matrix{};
      };
}

#endif
