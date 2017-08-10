#ifndef NUMPP_STRUCTURES_MATRICES_HPP_
#define NUMPP_STRUCTURES_MATRICES_HPP_

/**
  \defgroup numpp_structures_matrices Matrices
  \ingroup numpp_structures
  \brief Module containing different matrix implementation

  \warning <b>Compile-time implementation of dense matrix will be inefficient for bigger matrices compile-wise, but runtime is much faster.\n Sparse vector isn't be affected by this way of implementation</b>

  This is a summary header including every matrix structure provided by numpp.

  <b>\warning If you are looking for more compile-runtime balanced implementations check Eigen, Armadillo or other libraries</b>

  \code
  #include"numpp/structures/matrices.hpp"
  \endcode

*/

#include"./dense.hpp"
#include"./sparse.hpp"

#endif
