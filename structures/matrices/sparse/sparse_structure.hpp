#ifndef MATRICES_SPARSE_BLOCK_HPP_
#define MATRICES_SPARSE_BLOCK_HPP_

//PASS ALIGNMENT WITH g++ -DALIGNEMENT=`getconf LEVEL1_DCACHE_LINESIZE` for linux

#ifndef ALIGNMENT
#define ALIGNMENT 64
#endif

/* #ifndef NON_ZERO_THRESHOLD */
/* #define NON_ZERO_THRESHOLD 8 //FOR DOUBLES */
/* #endif */

#include<vector>
#include<iostream>
#include<thread>
#include<algorithm>
#include<cmath>
#include<algorithm>


namespace numpp::matrix{
  template<typename T, std::size_t Rows, std::size_t Columns>
    //VERSION WITH MAXIMUM POSSIBLE CACHE HIT
    //ANALYZE BLOCK STRUCTURE WHERE THIS STYLE IS PREFFERED
    class sparse{
      public:
        using value_type = T;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using reference = T&;
        using const_reference = const T&;
        using pointer = T*;
        using const_pointer = const T*;

        sparse(std::initializer_list<std::initializer_list<T>> elements){
          size_t i = 0;
          for(const auto& row: elements){
            matrix[i] = clear_from_zeroes(elements);
            ++i;
          }
        }
        /* sparse(std::initializer_list<T> elements){ */
        /*   std::vector<T> non_zero_elements = clear_from_zeroes(elements); */
        /*   unsigned int threads_available = std::thread::hardware_concurrency(); */

        /*   /1* if(non_zero_elements>NON_ZERO_THRESHOLD) *1/ */
        /*   if(threads_available > 1){ */
        /*     size_t threads_count = */
        /*       ((non_zero_elements.size()/threads_available) > NON_ZERO_THRESHOLD) */
        /*       ? threads_available */
        /*       : std::floor(non_zero_elements.size()/NON_ZERO_THRESHOLD) */
        /*       ; */

        /*     matrix.reserve(threads_count); */
        /*     size_t elements_per_thread = static_cast<size_t>(non_zero_elements.size()/threads_count); */
        /*     auto sentinel = begin(non_zero_elements)+1; */

        /*     for(size_t i=0; i<threads_count; ++i){ */

        /*       auto begin_per_thread = sentinel + elements_per_thread; */
        /*       if(begin_per_thread > end(non_zero_elements)){ */
        /*         matrix.emplace_back(std::vector<T>{sentinel, end(non_zero_elements)}); */
        /*         break; */
        /*       } */
        /*       auto new_sentinel = std::find( */
        /*           begin_per_thread, */
        /*           end(non_zero_elements), */
        /*           0); */

        /*       matrix.emplace_back(std::vector<T>{sentinel, new_sentinel}); */
        /*       sentinel = new_sentinel+1; */
        /*     } */
        /*   } */
        /*   else */
        /*     matrix.emplace_back(std::move(non_zero_elements)); */
        /* } */

        //COMPARISON FUNCTIONS
        /* bool operator==(const sparse<T>& a)const { */
        /*   return non_zero_elements==a.non_zero_elements; */
        /* } */

        /* bool operator!=(const sparse<T>& a)const { */
        /*   return !(*this==a); */
        /* } */

        /* //SIZE FUNCTIONS */
        /* size_type size()const noexcept{ */
        /*   return non_zero_elements.size(); */
        /* } */

        /* size_type max_size()const noexcept{ */
        /*   return non_zero_elements.max_size(); */
        /* } */

        void print()const noexcept{
          for(const auto& thread: matrix){
            for(const auto& elem: thread)
              std::cout << elem << std::endl;
            endl(std::cout);
          }
          endl(std::cout);
        }

      private:
        std::vector<T> clear_from_zeroes(std::initializer_list<T> elements){
          std::vector<T> non_zero_elements{};
          size_t elements_counter = 0;
          bool chain = false;
          for(const auto& element: elements){
            if(element!=0){
              if(chain)
                non_zero_elements.emplace_back(element);
              else{
                non_zero_elements.emplace_back(0);
                non_zero_elements.emplace_back(elements_counter);
                non_zero_elements.emplace_back(element);
                chain = true;
              }
            }
            else if(chain)
              chain = false;
            ++elements_counter;
          }

          non_zero_elements.shrink_to_fit();
          return non_zero_elements;
        }

        alignas(ALIGNMENT) std::array<std::vector<T>, Rows> matrix{};
    };
}

#endif
