#include "../../utilities/catch.hpp"
#include"numpp/roots/bisection.hpp"

TEST_CASE(
    "bisection basic tests"
    "[roots][bisection]"
    ){

  class Function{
    public:
      constexpr Function()=default;
      constexpr double operator()(const double x){
        return x*x*x - x -2;
      }
  };

  SECTION("basic bisection tests"){
    constexpr auto result1 = numpp::roots::bisection(Function{}, 1., 2.);
    constexpr auto result2 = numpp::roots::bisection(Function{}, 1., 2., 16);
    constexpr auto result3 = numpp::roots::bisection(Function{}, 1., 2., 0.000001, 1000);
    SECTION("correct results"){
      REQUIRE(result2 == Approx(1.5213928));
    }
    SECTION("auto epsilon vs set epsilon"){
      REQUIRE(result1 == Approx(result3));
    }
    SECTION("set iterations vs set epsilon"){
      REQUIRE(result2 == Approx(result3));
    }
  }

}
