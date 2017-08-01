#ifndef NUMPP_SYMBOLIC_FUNCTIONS_HPP_
#define NUMPP_SYMBOLIC_FUNCTIONS_HPP_

#include"arithmetic.hpp"

namespace numpp::differentiation::symbolic{
  //DIFFERENTIATE N-TH ORDER WITH RESPECT TO GIVEN VARIABLES
  //OVERALL RECURSIVE CASE
  template<typename Function, std::size_t Order>
    class differentiate{
      public:
      template<std::size_t Variable, std::size_t... Variables>
        using with_respect_to =
          typename differentiate<typename Function::template derivative<Variable>, Order-1>::template with_respect_to<Variables...>;

    };

  //BASE RECURSIVE CASE
  template<typename Function>
    class differentiate<Function, 1>{
      public:
        template<std::size_t Variable>
          using with_respect_to =
            typename Function::template derivative<Variable>;

    };

}

#endif
