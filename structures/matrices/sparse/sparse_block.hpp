#ifndef NUMPP_STRUCTURES_MATRICES_SPARSE_BLOCK_HPP_
#define NUMPP_STRUCTURES_MATRICES_SPARSE_BLOCK_HPP_

#include<vector>

#include"../../vector/vector_utils.hpp"

namespace numpp::matrix::sparse{
  template<typename T, std::size_t Rows, std::size_t Columns>
/**
\ingroup numpp_structures_matrices_sparse

\class block

\tparam T arithmetic type contained in matrix class
\tparam Rows number of rows in matrix
\tparam Columns number of columns in matrix

\brief Block version of sparse matrix

<b>This implementation is an experiment in cache hit-rate.\n </b>
Whole sparse matrix is contained in one array, divided based on blocks of contiguous non-zero numbers.\n
After each block operation calculating row is performed.

\warning <b>For parallelization of the sparse matrix dense vector multiplication you need compiler with OpenMP support</b>
\warning Only sparse matrix dense vector multiplication implemented
\warning <b>Each row has to be seperate std::initializer_list</b>

<b>Pros:</b>
- Obviously lower memory overhead, for 50% sparse matrix with no blocks it contains only 150% storage of dense matrix.
- Higher cache locality (at least in theory)

<b>Cons:</b>
- Impossible SIMD optimization
- Additional operations of read for every block

<b>Example:</b>
\code
numpp::matrix::sparse::nested<double, 3,3> mat{{0,  0,   1},
                                                {0,  2.3, 0},
                                                {0,  0,   13.7}
                                               };
constexpr numpp::matrix::vector<double, 3> vec{1,2,3};
auto result = mat*vec;
\endcode


\code
#include"numpp/structures/matrices/sparse.hpp"
\endcode

*/
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

          /**
             Function multiplying sparse matrix and dense vector

             \param vec Vector which will be multiplied
             \returns vector<U, Rows, false>
          */

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
