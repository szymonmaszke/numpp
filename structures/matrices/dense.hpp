#ifndef NUMPP_STRUCTURES_MATRICES_DENSE_HPP_
#define NUMPP_STRUCTURES_MATRICES_DENSE_HPP_

/**
  \defgroup numpp_structures_matrices_dense Dense
  \ingroup numpp_structures_matrices
  \brief Module containg constexpr dense matrix implementation

  <b>\warning Compilation time of this matrix may mitigate any runtime speedup.\n
  For dissertation of the problem see /ref praca </b>

  This matrix implementation uses heavy TMP tricks and C++17 functionality is required in order for it to work.

  <b>\warning If you are looking for more compile-runtime balanced implementations check Eigen, Armadillo or other libraries</b>

  <b>Example:</b>
  \code
  //Declaration of matrix
  numpp::matrix::dense<double, 3, 3> mat{
                                                0,  2,   3.15
                                                4,  8,   12,
                                                5., 7.7, 4.2
                                                };
  //Perform matrix multiplication
  //Other operations have operator overloaded as well
  auto new = mat*mat;
  //Operation against scalar
  auto divided = mat/3.14;

  auto transposed = transpose(mat);

  //Uses iterators, so you can print it this way:
  for(const auto& row: mat){
    for(const auto& elem: row)
      std::cout << elem << " ";
    std::cout << std::endl;
  }

  \endcode


  \code
  #include"numpp/structures/matrices/dense"
  \endcode

*/

#include"./dense/functions.hpp"
#include"./dense/mathematical.hpp"
#include"./dense/operations.hpp"
#include"./dense/structure.hpp"
#include"./dense/utils.hpp"
#include"../vector.hpp"

#endif
