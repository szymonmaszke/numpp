#include "../../../../utilities/catch.hpp"
#include "numpp/structures/matrices/dense.hpp"

TEST_CASE(
		"dense matrix operations tests",
		"[operations][matrix][dense]"
){
	constexpr numpp::matrix::dense<double, 4, 5> mat_a{
		1.2, -4.5, 12412.3, 12512., 294.2352,
		2, 5.35, -412.3, 12, 0,
		-34, 0, 0, 0, 4.5,
		3, 1.3, 1.7, 0, 0.1
	};

	constexpr numpp::matrix::dense<double, 3, 3> mat_b{
		1.2, -4.5, 12412.3,
		2, 5.35, -412.3,
		-34, 0, 1.1
	};

	constexpr numpp::matrix::dense<double, 4, 5> mat_c{
		13.323, 2481.2, 3., 12512., 2,
		55.5, 5., 12.3, 5096., 0,
		-34.4353, 0, 69.99999999999, 0, 9638903.5,
		3385, 1, 19.5820, 1, 0
  };

	constexpr numpp::matrix::dense<double, 5, 3> mat_d{
		1.2, -4.5, 12412.3,
		2, 5.35, -412.3,
		-34, 0, 0,
    924.535, 39.58395, -21892,
    -1e-6, 35.424,0.00024
	};


	SECTION("std::get tests"){
		REQUIRE(numpp::matrix::get<0>(mat_a) == Approx(1.2));
		REQUIRE(numpp::matrix::get<6>(mat_a) == Approx(5.35));
		REQUIRE(numpp::matrix::get<8>(mat_a) == Approx(12));
		REQUIRE(numpp::matrix::get<4>(mat_a) == Approx(294.2352));
		REQUIRE(numpp::matrix::get<7>(mat_a) == Approx(-412.3));
		REQUIRE(numpp::matrix::get<14>(mat_a) == Approx(4.5));
		REQUIRE(numpp::matrix::get<19>(mat_a) == Approx(0.1));

		REQUIRE(numpp::matrix::get<1>(mat_b) == Approx(-4.5));
		REQUIRE(numpp::matrix::get<2>(mat_b) == Approx(12412.3));
		REQUIRE(numpp::matrix::get<3>(mat_b) == Approx(2));
		REQUIRE(numpp::matrix::get<4>(mat_b) == Approx(5.35));
		REQUIRE(numpp::matrix::get<5>(mat_b) == Approx(-412.3));
		REQUIRE(numpp::matrix::get<7>(mat_b) == Approx(0));
		REQUIRE(numpp::matrix::get<8>(mat_b) == Approx(1.1));
  }

  SECTION("Constexpr basic arithmethic between matrices"){
    constexpr auto temp = mat_a + mat_c;
    REQUIRE(temp(1,1) == Approx(10.35));
    REQUIRE(temp(0,2) == Approx(12415.3));
    constexpr auto temp2 = temp - mat_a;
    REQUIRE(temp2(3,2) == Approx(mat_c(3,2)));
    REQUIRE(temp2(3,2) == Approx(mat_c(3,2)));
    constexpr auto temp3 = 5 * temp2;
    REQUIRE(temp3(1,0) == Approx(temp2(1,0)*5));

    constexpr auto temp4 = mat_c * mat_d;
    REQUIRE(temp4(3,0) == Approx(4322.747));
    REQUIRE(temp4(1,1) == Approx(201496.8092));
  }
}
