#include "../../../../utilities/catch.hpp"
#include "numpp/structures/matrices/normal/normal_functions.hpp"
/* #include "../../../../../structures/matrices/normal/normal_functions.hpp" */

TEST_CASE(
		"normal matrix functions tests",
		"[functions][matrix][normal][constexpr]"
){
	constexpr numpp::matrix::normal<double, 4, 5> matrix{
		1.2, -4.5, 12412.3, 12512., 294.2352,
		2, 5.35, -412.3, 12, 0,
		-34, 0, 0, 0, 4.5,
		3, 1.3, 1.7, 0, 0.1
	};


	SECTION("transposition tests"){
		constexpr auto transposed_matrix = transpose(matrix);
		REQUIRE(transposed_matrix(0,1) == Approx(2));
		REQUIRE(transposed_matrix(1,0) == Approx(-4.5));
		REQUIRE(transposed_matrix(1,2) == Approx(0));
		REQUIRE(transposed_matrix(2,4) == Approx(1.7));
		REQUIRE(transposed_matrix(3,2) == Approx(12));
		REQUIRE(transposed_matrix(4,3) == Approx(0.1));
  }

  SECTION("is matrix square?"){
    REQUIRE_FALSE(square(matrix));
    constexpr numpp::matrix::normal<double, 2,2> foo{1,1,1,1};
    REQUIRE(square(foo));
  }
}
