#ifndef NUMPP_SYMBOLIC_TYPES_HPP_
#define NUMPP_SYMBOLIC_TYPES_HPP_

#include<type_traits>

namespace numpp::differentiation::symbolic{
  template<typename T>
    class variable{
      public:
        using active = std::true_type;
        using derivative = variable<T>;
        using type = T;

        constexpr T operator()(T value)const{
          return value;
        }
    };

  template<typename T>
    class inactive{
      public:
        using active = std::false_type;
        using derivative = inactive<T>;
        using type = T;

        constexpr T operator()(T variable)const{
          return variable;
        }
    };

  class none{
    template<typename U>
      constexpr U operator()(U dummy...){
        return 0;
      }
  };

  template<int Value>
    class constant{
      using active = std::false_type;
      using derivative = none;
      using type = int;

      template<typename ...U>
        constexpr int operator()(U ...){
          return Value;
        }

    };

}

#endif
