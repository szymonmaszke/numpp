#include"normal_structure.hpp"

namespace numpp::matrix{
  template<std::size_t Index, typename T, std::size_t Rows, std::size_t Columns>
      constexpr T& get(normal<T, Rows, Columns>& n){
        constexpr std::size_t row = static_cast<std::size_t>(Index/(Columns));
        constexpr std::size_t col= Index%Columns;
        return n(row, col);
      }

  template<std::size_t Index, typename T, std::size_t Rows, std::size_t Columns>
      constexpr T& get(normal<T, Rows, Columns>&& n){
        constexpr std::size_t row = static_cast<std::size_t>(Index/(Columns));
        constexpr std::size_t col= Index%Columns;
        return std::move(n(row,col));

      }

  template<std::size_t Index, typename T, std::size_t Rows, std::size_t Columns>
      constexpr const T& get(const normal<T, Rows, Columns>& n){
        constexpr std::size_t row = static_cast<std::size_t>(Index/(Columns));
        constexpr std::size_t col= Index%Columns;
        return n(row, col);
      }

  template<std::size_t Index, typename T, std::size_t Rows, std::size_t Columns>
      constexpr const T&& get(const normal<T, Rows, Columns>&& n){
        constexpr std::size_t row = static_cast<std::size_t>(Index/(Columns));
        constexpr std::size_t col= Index%Columns;
        return std::move(n(row,col));
      }
}


namespace std {
  template<typename T, std::size_t Rows, std::size_t Columns>
    class tuple_size<numpp::matrix::normal<T,Rows,Columns>> :
    public integral_constant<std::size_t, Rows*Columns>
      {};

  template<std::size_t Index, typename T, std::size_t Rows, std::size_t Columns>
    class tuple_element<Index, numpp::matrix::normal<T,Rows,Columns>>
    {
      public:
        using type = T;
    };
}
