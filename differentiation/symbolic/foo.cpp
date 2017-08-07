#include"../symbolic.hpp"
#include<iostream>
#include<typeinfo>

namespace nds = numpp::differentiation::symbolic;

int main(){
  using Function = nds::simplify_multiplication<nds::constant<3>, nds::simplify_multiplication<nds::cosinus<nds::x<0>>, nds::constant<2>>>;
  std::cout << typeid(Function).name() << std::endl;
}
