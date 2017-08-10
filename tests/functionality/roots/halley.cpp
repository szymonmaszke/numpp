#include "../../utilities/catch.hpp"
#include"numpp/roots/roots.hpp"
#include"numpp/differentiation/symbolic.hpp"
#include"numpp/differentiation/automatic.hpp"
#include"numpp/differentiation/finite.hpp"
#include<tuple>

TEST_CASE(
    "bisection basic tests",
    "[roots][halley][constexpr]"
    ){

  class Function{
    public:
      constexpr Function()=default;
      constexpr double operator()(const double x){
        return x*x*x - x -2;
      }
  };

  class Derivative{
    public:
      constexpr auto operator()(const double x){
        return numpp::differentiation::finite::central(Function{}, x);
      }
  };

  class SecondDerivative{
    public:
      constexpr auto operator()(const double x){
        return 6*x;
      }
  };

  namespace nds = numpp::differentiation::symbolic;
  using TypeFunction = decltype(nds::pow<3>(nds::x<0>{}) - nds::x<0>{} - nds::constant<2>{});
  using TypeDerivative = nds::differentiate<TypeFunction, 1>::with_respect_to<0>;
  using TypeSecondDerivative = nds::differentiate<TypeDerivative, 1>::with_respect_to<0>;

  SECTION("basic newton tests"){
    constexpr auto symbolic = numpp::roots::halley<
      TypeFunction,
      TypeDerivative,
      TypeSecondDerivative>(5.);
    constexpr auto finite = numpp::roots::halley(
        5.,
        Function{},
        Derivative{}, SecondDerivative{}
        );
    SECTION("symbolic overload"){
      REQUIRE(symbolic == Approx(1.5213928));
    }
    SECTION("finite overload"){
      REQUIRE(finite == Approx(symbolic));
    }
  }

}
