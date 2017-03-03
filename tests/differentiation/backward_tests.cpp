#include "../catch.hpp"
#include "../../differentiation/backward.hpp"

TEST_CASE(
		"backward finite difference tests",
		"[differentiation][backward]"
    ){

  class example_function{
    public:
      constexpr double operator()(const double x)const{
        return (((x*(x+4))*3)*x)
          /((x+13.37)*7);
      }
  };
  constexpr example_function f{};

  SECTION("basic result tests"){
    constexpr auto result1 = numpp::derivative::backward(f, 3.1415, 0.00001);
    constexpr auto result2 = numpp::derivative::backward(f, 3.1415);
    SECTION("correct results"){
      REQUIRE(result2 == Approx(1.31001));
    }
    SECTION("set h vs auto h"){
      REQUIRE(result1 == Approx(result2));
    }
  }

}
