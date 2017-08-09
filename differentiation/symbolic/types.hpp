#ifndef NUMPP_DIFFERENTIATION_SYMBOLIC_TYPES_HPP_
#define NUMPP_DIFFERENTIATION_SYMBOLIC_TYPES_HPP_

#include<type_traits>

namespace numpp::differentiation::symbolic{

/**
\ingroup numpp_differentiation_symbolic

\class constant

\brief Class representing constant integer number

\tparam Value integer value contained in constant object

\code
#include"numpp/differentiation/symbolic.hpp"
\endcode

*/

  template<int Value>
    class constant{
      public:
        using active = std::false_type;
        template<std::size_t Active> using derivative = constant<0>;
        using type = int;

/**
  \brief Returns Value no matter the argument
  \returns int
*/

        constexpr static int calculate(auto&&){
          return Value;
        }

    };

/**
\ingroup numpp_differentiation_symbolic

\class variable

\brief Class representing variable of any type

\tparam T type of value in variable (e.g. double)
\tparam Number integer value differentiating variable from every other variable object

\code
#include"numpp/differentiation/symbolic.hpp"
\endcode

*/

  template<typename T, std::size_t Number>
    class variable{
      public:
        template<std::size_t Active>
          using derivative = std::conditional_t<
          Active==Number,
          constant<1>,
          constant<0>
        >;

/**
  \brief Returns value of a certain variable

  \details For example:
  \code
  auto z = nds::variable<double, 3>::calculate(double[5]{0,1,2,3,4});
  std::cout << z << std::endl;
  //Will return 2, because it's the 3rd index specified in variable
  \endcode

  \returns int
*/
        constexpr static auto calculate(auto&& values){
          return values[Number];
        }
    };

/**
  \ingroup numpp_differentiation_symbolic
  \brief Convenience alias for variable with specified variable type as double

*/
  template<std::size_t Number> using x = variable<double, Number>;

}

#endif
