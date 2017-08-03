#ifndef NUMPP_DIFFERENTIATION_SYMBOLIC_TYPES_HPP_
#define NUMPP_DIFFERENTIATION_SYMBOLIC_TYPES_HPP_

#include<type_traits>

namespace numpp::differentiation::symbolic{

  template<int Value>
    class constant{
      public:
        using active = std::false_type;
        template<std::size_t Active> using derivative = constant<0>;
        using type = int;

        constexpr static int calculate(auto&&){
          return Value;
        }

    };

  template<typename T, std::size_t Number>
    class variable{
      public:
        template<std::size_t Active>
          using derivative = std::conditional_t<
          Active==Number,
          constant<1>,
          constant<0>
        >;

        constexpr static auto calculate(auto&& values){
          return values[Number];
        }
    };

  template<std::size_t Number> using x = variable<double, Number>;

}

#endif
