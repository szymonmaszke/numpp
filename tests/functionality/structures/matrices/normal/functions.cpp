#include "../../../../utilities/catch.hpp"
#include "numpp/structures/matrices/dense.hpp"

TEST_CASE(
		"dense matrix functions tests",
		"[functions][matrix][dense][constexpr]"
){
  constexpr numpp::matrix::dense<int, 3, 4> matrix{
    1,2,3,4,
    5,6,7,8,
    9,10,11,12
  };



	SECTION("transposition tests"){
		constexpr auto transposed_matrix = transpose(matrix);
		REQUIRE(transposed_matrix(0,1) == Approx(5));
		REQUIRE(transposed_matrix(1,0) == Approx(2));
		REQUIRE(transposed_matrix(1,2) == Approx(10));
		REQUIRE(transposed_matrix(2,1) == Approx(7));
		REQUIRE(transposed_matrix(3,0) == Approx(4));
  }

  SECTION("is matrix square?"){
    REQUIRE_FALSE(square(matrix));
    constexpr numpp::matrix::dense<double, 2,2> foo{1,1,1,1};
    REQUIRE(square(foo));
  }
}
