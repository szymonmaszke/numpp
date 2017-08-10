#ifndef NUMPP_DIFFERENTIATION_SYMBOLIC_HPP_
#define NUMPP_DIFFERENTIATION_SYMBOLIC_HPP_

/** \defgroup numpp_differentiation_symbolic Symbolic Differentiation
  \ingroup numpp_differentiation

  \brief This module provides the means for performing symbolic differentiation

  \code
  numpp/differentiation/symbolic.hpp #includes every method in the module
  numpp/differentiation/symbolic/SUBCLASS.hpp #include specific SUBCLASS
  \endcode

  \warning <b>Second include option SHOULDN'T be used</b>

  Idea developed independently, but merged with the research paper
  <a href="https://arxiv.org/abs/1705.01729">Compile Time Symbolical Differentiation 2017</a> and many ideas based on theirs.
  \n<b>Thank you for this paper, most of the credits belong to them!
  Please refer to their paper for thourough speed comparison against automatic differentiation.</b>

  For differences mine and theirs application of the type differentiation see this paper:
  <a href="https://github.com"> numpp dissertation </a>
  \n For comparison against <a href="https://github.com/symengine/symengine">symengine</a>, base of <a href="http://www.sympy.org/en/index.html">SymPy</a>
  see these tests: <a href="https://github.com"> sympy vs numpp </a>

  <b>Details and usage:</b>

  Overloads for common mathemathical operations are provided (details in classes).\n
  Approach taken by type differentiating doesn't resemble well-known symbolic differentiation in C++,
  hence some examples are needed:

  \warning For convenience, in the following examples, namespace numpp::differentiation::symbolic is abbreviated as nds.

  <b>1. Variables and constants </b>

  Basing building blocks of the function. Can be defined as follows:
  \code
  nds::x<0> x0{};
  nds::x<1> x1{};
  \endcode

  Above x variables are implicilty of type double. To express type explicitly use:

  \code
  nds::variable<int, 0> x0{};
  \endcode

  Numeric parameter (of type std::size_t) differentiates every variable from the others.

  \code
  nds::constant<14> cons{};
  \endcode

  Currently only integer constants are supported.

  <b>2. Defining functions </b>

  We only have to define Function type, there is no need to create the object.\n
  Arithmetic operators and some other mathematical functions are overloaded for
  convenience in function defining.

  You should use the \code using and decltype() \endcode when defining it.

  <b>Example of \f$ \sin(\cos(\frac{x_0}{x_1})*\log(x_0)) + x_2 \f$ creation</b> :

  \code
  #include"numpp/differentiation/symbolic.hpp"

  using Function = decltype(sin(cos(nds::x<0>{}/nds::x<1>{})*log(nds::x<0>{})) + nds::x<2>{});
  \endcode

  <b>3. Differentiating the function:</b>

  There are two ways to differentiate type, as shown below:

  <b>3.1. Predicate with_respect_to:</b>
  \code
  //Function as defined above
  using Derivative = nds::differentiate<Function, 3>::with_respect_to<0,0,1>;
  \endcode

  Above code performs 3-rd order differentiation with respect to \f$x_0, x_0, x_1 \f$
  in this exact order.

  <b>3.2. With derivative type:</b>
  \code
  //Function as defined above
  using Derivative = Function::derivative<0>
  \endcode

  Above performs differentiation with respect to \f$x_0\f$.

  <b>4. Obtaining numerical values from expressions</b>

  After obtaining Function type (or Derivative or similiar) you would probably like to obtain
  value at a given point. \n
  To do so, you have to create an array which size is equal to the number of independent variables\n
  and pass it to the static constexpr function <b>calculate</b>

  <b>Example</b>

  \code
  //Derivative as defined above
  constexpr auto value = Derivative::calculate(std::array<double, 3>{1.,5.,7.});
  \endcode

  Any object providing operator[] may be used as an argument to calculate.


  <b>Technical Details:</b>

  Approach of type differentiating allows this module to obtain near hand-coded
  efficiency for n-th order partial derivatives.

  Cons - compilation may take longer as order and complexity of formula increases
  after this initial phase, every derivative evaluation or next differentiation
  will take substantially shorter amount of time than current available approaches.

  \namespace numpp::differentiation::symbolic


*/

#include"./symbolic/arithmetic.hpp"
#include"./symbolic/arithmetic_simplifier.hpp"
#include"./symbolic/exponential.hpp"
#include"./symbolic/functions.hpp"
#include"./symbolic/trigonometric.hpp"
#include"./symbolic/types.hpp"

#endif
