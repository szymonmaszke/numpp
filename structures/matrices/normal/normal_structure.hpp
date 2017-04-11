#ifndef MATRIXES_NORMAL_HPP
#define MATRIXES_NORMAL_HPP

#include<array>

namespace numpp::matrix{
  template<typename T, std::size_t Rows, std::size_t Columns>
    class normal{
      public:
        using value_type = T;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using reference = T&;
        using const_reference = const T&;
        using pointer = T*;
        using const_pointer = const T*;

        //COMPARISON FUNCTIONS
        constexpr bool operator==(const normal<T,Rows,Columns>& a)const {
          return matrix_==a.matrix_;
        }

        constexpr bool operator!=(const normal<T,Rows,Columns>& a)const {
          return !(*this==a);
        }

        //SIZE FUNCTIONS
        constexpr size_type size()const {
          return Rows*Columns;
        }
        constexpr size_type max_size()const {
          return Rows*Columns;
        }
        constexpr size_type row_size()const {
          return Rows;
        }
        constexpr size_type column_size()const {
          return Columns;
        }

        reference operator()(size_type row, size_type col) noexcept{
          return matrix_[row][col];
        }

        constexpr const_reference operator()(size_type row, size_type col) const{
          return matrix_[row][col];
        }

        std::array<std::array<T,Columns>,Rows> matrix_;
      };
}

#endif
