#ifndef NUMPP_DIFFERENTIATION_AUTOMATIC_FORWARD_HPP_
#define NUMPP_DIFFERENTIATION_AUTOMATIC_FORWARD_HPP_

/**
\defgroup numpp_differentiation_forward_automatic Forward Automatic Differentiation
\ingroup numpp_differentiation_automatic

\brief First order automatic differentiation in forward mode

\code
#include"numpp/differentiation/automatic/forward.h"
\endcode

You can use it almost in the same way as built-in arithmetic types, e.g.
addition, multiplication and other similiar operations are provided.

It is advised to use auto whenever possible to ease the need of explicit
namespace/class names providing.

You can use partial differentiation, but you have to specify the activity
parameter in the constructor (equal to 0 for inactive node), example shown below.

/warningIf you need derivatives of higher order it is advised to use symbolic differentiation
module for it's simplifying ability.

<b>Example: Calculating \f$ \frac{\partial z}{\partial x} \cos(x+y)*\sin(y) + 3 \f$:</b>
\code

//Active variable x with initial value of 6
numpp::differentiation::automatic::forward x{6};
//Inactive variable y with initial value of 4;
numpp::differentiation::automatic::forward y{4};
//Calculate value and partial derivative into two seperate variables
auto z = std::cos(x+y)*std::sin(y) + 3
std::cout << "Function value: " << z.value << std::endl;
std::cout << "Function derivative wrt x: " << z.derivative<< std::endl;
\endcode


\sa \red numpp_symbolic_differentiation "Symbolic Differentiation"

*/

#include"./forward/structure.hpp"
#include"./forward/functions.hpp"

#endif
