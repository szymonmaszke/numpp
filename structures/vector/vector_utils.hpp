#include"vector_structure.hpp"

namespace numpp{
  template<std::size_t Index, typename T, std::size_t Size, bool Transposition>
      constexpr T& get(numpp::vector<T, Size, Transposition>& v){
        return std::get<Index>(v.vector_);
      }

  template<std::size_t Index, typename T, std::size_t Size, bool Transposition>
      constexpr T&& get(numpp::vector<T, Size, Transposition>&& v){
        return std::get<Index>(std::move(v.vector_));
      }

  template<std::size_t Index, typename T, std::size_t Size, bool Transposition>
      constexpr const T& get(const numpp::vector<T, Size, Transposition>& v){
        return std::get<Index>(v.vector_);
      }

  template<std::size_t Index, typename T, std::size_t Size, bool Transposition>
      constexpr const T&& get(const numpp::vector<T, Size, Transposition>&& v){
        return std::get<Index>(std::move(v.vector_));
      }
}


namespace std {
  template<typename T, std::size_t Size, bool Tranposition>
    class tuple_size<numpp::vector<T,Size,Tranposition> > :
    public integral_constant<size_t, Size>{
    };

  template<std::size_t Index, typename T, std::size_t Size, bool Transposition>
    class tuple_element<Index, numpp::vector<T,Size,Transposition>>{
      public:
        using type = T;
    };
}
