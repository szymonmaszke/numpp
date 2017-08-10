#ifndef VECTOR_HPP
#define VECTOR_HPP
/**
  \defgroup numpp_structures_vector Vector
  \ingroup numpp_structures
  \brief Class representing one-dimensional numerical vector

  This class provides vector with it's basic functionality.
  Every operations should be done in compile time.

  <b>\warning This implementation is obviously faster in runtime,
  but the compilation time may mitigate the positive effects.\n

  <b>Example:</b>
  \code
  \\Create vector
  numpp::vector<double, 5> x{1,2,3,4,5}; //Implicit transposition equal to false
  numpp::vector<double, 5, true> y{1,2,3,4,5}; //Transposed vector

  double scalar = y*x //Returns scalar y^T * x
  auto matrix = x*y //Returns matrix of x * y^T

  std::cout << norm::euclidean(x) << std::endl; //prints euclidean norm of the vector
  \endcode

  <b>\warning If you are looking for more compile-runtime balanced implementations check Eigen, Armadillo or other libraries</b>

  \code
  #include"numpp/structures/vector.hpp"
  \endcode

*/

#include "vector/functions.hpp"
#include "vector/operations.hpp"
#include "vector/utils.hpp"
#include "vector/structure.hpp"
#include "vector/matrix_vector_operations.hpp"

#endif
