#ifndef NUMPP_DIFFERENTIATION_FINITE_HPP_
#define NUMPP_DIFFERENTIATION_FINITE_HPP_

/** \defgroup numpp_differentiation_finite Finite Differentiation
  \ingroup numpp_differentiation

  \brief This module provides the means for performing finite difference differentiation

  <b>Calculates the derivative by using finite difference formulas
  For higher order derivatives check \ref numpp_symbolic_differentiation Symbolic Differentiation </b>

  \warning For automatically calculated epsilon type has to fullfil std::is_floating_point trait.

  \warning To specify your own type used in automatic epsilon overload, you have to specialize is_floating_point STL trait.
  Such type has to provide additional epsilon trait and few other operations.

  \warning Check source code for more info.

  Namespace:
  \code
  numpp::differentiation::finite
  \endcode

  Include:
  \code
  numpp/differentiation/finite.hpp #includes every method in the module
  numpp/differentiation/automatic/SUBCLASS.hpp #include specific methods
  \endcode

  \warning <b>Second include option SHOULDN'T be used</b>

*/

#include"./finite_difference/backward.hpp"
#include"./finite_difference/central.hpp"
#include"./finite_difference/forward.hpp"

#endif
