#include"conjugate_gradient.hpp"
#include<iostream>

int main(){
  constexpr numpp::matrix::normal<double, 2, 2> matrix{4,1,1,3};
  constexpr numpp::vector<double, 2> x{2,1};
  constexpr numpp::vector<double, 2> b{1,2};
  auto foo = numpp::krylov::conjugate_gradient(matrix, b, x);

}
