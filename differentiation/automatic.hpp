#ifndef NUMPP_DIFFERENTIATION_AUTOMATIC_HPP_
#define NUMPP_DIFFERENTIATION_AUTOMATIC_HPP_

/** \defgroup numpp_differentiation_automatic Automatic Differentiation
  \ingroup numpp_differentiation

  \brief This module provides the means for performing automatic differentiation

  Only forward mode as of now, backward propagation should be provided later.

  <b>Only first order partial differentiation supported.

  For higher order derivatives check \ref numpp_differentiation_symbolic </b>

  \warning Only arithmetic types are backed by the implementation.
  To specify your own type, you have to specialize is_arithmetic STL trait.
  Such type has to provide overload for addition and mathematical oprations like
  sin, cos etc. (constexpr versions for GCC compiler)

  Namespace:
  \code
  numpp::differentiation::automatic
  \endcode

  Include:
  \code
  numpp/differentiation/automatic.hpp #includes every method in the module
  numpp/differentiation/automatic/SUBCLASS.hpp #include specific SUBCLASS
  \endcode

  \warning <b>Second include option SHOULDN'T be used</b>

*/

#include"./automatic/forward.hpp"

#endif
