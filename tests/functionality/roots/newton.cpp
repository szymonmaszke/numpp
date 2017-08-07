#include "../../utilities/catch.hpp"
#include"numpp/roots/roots.hpp"
#include"numpp/differentiation/symbolic.hpp"
#include"numpp/differentiation/automatic.hpp"
#include"numpp/differentiation/finite.hpp"
#include<tuple>

TEST_CASE(
    "bisection basic tests",
    "[roots][newton][constexpr]"
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
        return numpp::derivative::finite::central(Function{}, x);
      }
  };

  class AutomaticFunction{
    public:
      constexpr auto operator()(const double val){
        numpp::differentiation::automatic::forward<double> x{val};
        auto function= x*x*x - x - 2;
        return std::make_tuple(function.value, function.derivative);
      }
  };

  namespace nds = numpp::differentiation::symbolic;
  using TypeFunction = decltype(nds::pow<3>(nds::x<0>{}) - nds::x<0>{} - nds::constant<2>{});
  using TypeDerivative = nds::differentiate<TypeFunction, 1>::with_respect_to<0>;

  SECTION("basic newton tests"){
    constexpr auto symbolic = numpp::roots::newton<TypeFunction, TypeDerivative>(5.);
    constexpr auto finite = numpp::roots::newton(Function{}, Derivative{}, 5.);
    constexpr auto automatic = numpp::roots::newton(AutomaticFunction{}, 5.);
    SECTION("symbolic overload"){
      REQUIRE(symbolic == Approx(1.5213928));
    }
    SECTION("finite overload"){
      REQUIRE(automatic == Approx(symbolic));
    }
    SECTION("automatic overload"){
      REQUIRE(finite == Approx(automatic));
    }
  }

}
