#ifndef NUMPP_DIFFERENTIATION_SYMBOLIC_FUNCTIONS_HPP_
#define NUMPP_DIFFERENTIATION_SYMBOLIC_FUNCTIONS_HPP_

#include"arithmetic.hpp"

namespace numpp::differentiation::symbolic{
/**
\ingroup numpp_differentiation_symbolic

\class differentiate

\brief Allows differentiation of N-th order

\tparam Function Function which should be differentiated, see /ref numpp_differentiation_symbolic "tutorial" for more info
\param Order order of the differentiation, e.g. 3 for 3rd order

\code
#include"numpp/differentiation/symbolic.hpp"
\endcode

*/
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
