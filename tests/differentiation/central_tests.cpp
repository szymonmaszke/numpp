#include "../catch.hpp"
#include "../../differentiation/central.hpp"

TEST_CASE(
		"central finite difference tests",
		"[differentiation][central]"
    ){

  class example_function{
    public:
      constexpr double operator()(double x){
        return std::pow(std::pow(x,3.33)/(x+123),4)
          /std::hypot(std::sqrt(x+12.1) ,std::pow(x-3.14, 2));
      }
  };
  example_function f{};

  SECTION("basic result tests"){
    constexpr auto result1 = numpp::derivative::central(f, 2.53, 0.00001);
    constexpr auto result2 = numpp::derivative::central(f, 2.53);
    SECTION("correct results"){
      REQUIRE(result1 == Approx(0.0012835));
    }
    SECTION("set h vs auto h"){
      REQUIRE(result1 == Approx(result2));
    }
  }

}
