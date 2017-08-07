#include "../../utilities/catch.hpp"
#include"numpp/krylov/conjugate_gradient.hpp"
/* #include"../../../krylov/conjugate_gradient.hpp" */

TEST_CASE(
    "conjugate gradient basic test",
    "[krylov][constexpr][conjugate][gradient][matrix]"
    ){

  SECTION("basic conjugate gradient test"){
    constexpr numpp::matrix::dense<double, 3, 3> A{
      21.37, 81.84, -402,
      81.84,     2,   0,
       -402,     0, 7134
    };
    constexpr numpp::vector<double, 3> x{1,1,1};
    constexpr numpp::vector<double, 3> b{2.137, -24.3, -112};

    SECTION("correct results"){
      constexpr auto result = numpp::krylov::conjugate_gradient(A, x, b);
      REQUIRE(result(0)== Approx(-0.295561));
      REQUIRE(result(1)== Approx(-0.0556365));
      REQUIRE(result(2)== Approx(-0.0323543));
    }
  }

}
