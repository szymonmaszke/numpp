#ifndef NUMPP_STRUCTURES_HPP_
#define NUMPP_STRUCTURES_HPP_

/**
  \defgroup numpp_structures Structures
  \brief This modules provides basic algebraic structures like matrices and vectors

  <b>\warning Operations on those structures are MUCH faster in runtime, BUT, especially for large size objects,
  suffer from MUCH longer compilation times.\n Often it may not be desirable. If that's your case,
  than I urge you to try other, better established libraries like Armadillo or Eigen </b>
*/

#include"./vector.hpp"
#include"./matrices/dense.hpp"
#include"./matrices/sparse.hpp"

#endif
