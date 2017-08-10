#ifndef NUMPP_STRUCTURES_MATRICES_SPARSE_BLOCK_NESTED_HPP_
#define NUMPP_STRUCTURES_MATRICES_SPARSE_BLOCK_NESTED_HPP_

#include<vector>

#include"../../vector/vector_utils.hpp"


namespace numpp::matrix::sparse{
  namespace impl{
    template<typename T>
      struct inner_block{
        public:
          std::vector<T> data;
          std::size_t column;
      };
  }
  //BLOCK OF CONTIGUOUS DATA IN MATRIX

/**
\ingroup numpp_structures_matrices_sparse

\class nested

\tparam T arithmetic type contained in matrix class
\tparam Rows number of rows in matrix
\tparam Columns number of columns in matrix

\brief Block nested version of sparse matrix

<b>This implementation is an experiment in cache hit-rate.\n </b>
Whole sparse matrix is contained in one array, inside there is a nested block which contains each data block
After each block operation calculating row is performed.

\warning <b>For parallelization of the sparse matrix dense vector multiplication you need compiler with OpenMP support</b>
\warning Only sparse matrix dense vector multiplication implemented
\warning <b>Each row has to be seperate std::initializer_list</b>

<b>Pros:</b>
- Even smaller memory overhead than numpp::matrix::sparse::block (one less element per block kept in memory)
- Higher possibility of SIMD optimization than above

<b>Cons:</b>
- Additional operations of read for every block
- Cache locality may be worse as two vectors are nested inside each other

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
  template<typename T, std::size_t Rows, std::size_t Columns>
      //VERSION WITH MAXIMUM POSSIBLE CACHE HIT
      //ANALYZE BLOCK STRUCTURE WHERE THIS STYLE IS PREFFERED
      class nested{
        public:
          using value_type = T;
          using size_type = std::size_t;
          using reference = T&;
          using const_reference = const T&;
          using pointer = T*;
          using const_pointer = const T*;

          nested()=default;
          nested(const nested&)=default;
          nested(nested&&)=default;
          nested& operator=(nested&&)=default;
          nested& operator=(const nested&)=default;

          nested(std::initializer_list<std::initializer_list<T>> elements){

            for(auto row=std::begin(elements); row!=std::end(elements); ++row){
              std::size_t elements_counter = 0;
              const auto iterator_position{std::distance(std::begin(elements), row)};

              for(auto col=row->begin(), end=row->end(); col!=end; ++col){
                if(*col != 0){
                  inner_block<T> chain{};
                  chain.column = elements_counter;

                  while((*col != 0) && (col!=end)){
                    chain.data.push_back(*col);
                    ++elements_counter;
                    ++col;
                  }
                  matrix[iterator_position].emplace_back(chain);
                }
                ++elements_counter;
              }
            }
          }

          size_type size() const noexcept{
            return matrix.size();
          }

          /**
            Returns underlying data structure
            */
          const std::array<std::vector<impl::inner_block<T>>, Rows>& data() const noexcept{
            return matrix;
          }

          /**
            Returns underlying data structure
            */
          std::array<std::vector<impl::inner_block<T>>, Rows>& data() noexcept{
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

                for(std::size_t inner_block=0, block_end=matrix[row].size(); inner_block<block_end; ++inner_block){

                  const std::size_t col=matrix[row][inner_block].column;
                  const std::size_t element_end=matrix[row][inner_block].data.size();
                  #pragma omp simd
                  for(std::size_t element=0; element<element_end; ++element){
                    output(row) += matrix[row][inner_block].data[element]*vec(col+element);
                  }
                }

              }
              return output;
            }

        private:
          std::array<std::vector<impl::inner_block<T>>, Rows> matrix{};
      };
}

#endif
