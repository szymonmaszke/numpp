#include "../../../../utilities/catch.hpp"
/* #include "numpp/structures/matrices/normal/normal_functions.hpp" */
#include "../../../../../structures/matrices/normal/mathemathical.hpp"

TEST_CASE(
		"normal matrix functions tests",
		"[mathemathical][matrix][normal][constexpr]"
){
	constexpr numpp::matrix::normal<double, 4, 5> matrix{
		1.2, -4.5, 12412.3, 12512., 294.2352,
		2, 5.35, -412.3, 12, 0,
		-34, 0, 0, 0, 4.5,
		3, 1.3, 1.7, 0, 0.1
	};


	SECTION("log tests"){
		constexpr auto matrix_log = std::log(matrix);
    REQUIRE(matrix_log(1,1) == std::log(matrix(1,1)));
    REQUIRE(matrix_log(2,3) == std::log(matrix(2,3)));
  }
	SECTION("pow tests"){
		constexpr auto matrix_pow = std::pow(matrix, 2);
    REQUIRE(matrix_pow(1,1) == std::pow(matrix(1,1)));
    REQUIRE(matrix_pow(2,3) == std::pow(matrix(2,3)));
  }
}
