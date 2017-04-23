#include "../../../utilities/catch.hpp"
#include "../../../../structures/vector/vector_operations.hpp"

TEST_CASE(
		"vector basic functionality tests",
		"[structure][vector][normal][compile-time]"
){
	constexpr numpp::vector<double, 6> vec1{3, 4.545, 123, 25.33, 0, 1.2};
	numpp::vector<double, 6, true> vec2{0, 12, 1244.1337, 25.33, .1, .243125};
	constexpr auto vec3{vec1};
	REQUIRE(vec1 == vec3);

	SECTION("Constructor magic tests"){
		//Constructs vector no matter the transposition, but only explicitly
		//User needs to provide the desired type somewhere along the way
		numpp::vector<double, 6> temp{vec2};
		temp = vec1;
		numpp::vector<double, 6, true> temp2{std::move(temp)};
		REQUIRE(temp2 == vec1);
	}

	SECTION("Utility functions test"){
		constexpr numpp::vector<long, 3> temp{};
		REQUIRE(temp.transposed() == false);
		REQUIRE(temp.size() == 3);
		REQUIRE(temp.size() == temp.max_size());
    REQUIRE(numpp::get<0>(vec1) == Approx(3));
	}

	SECTION("Comparison functions test"){
		numpp::vector<double, 6> temp{vec2};
		REQUIRE(temp == vec2);
		REQUIRE(vec1 == vec3);
		REQUIRE_FALSE(vec2 == vec3);
		REQUIRE(temp != vec1);
	}
	SECTION("Reference operators"){
		REQUIRE(vec1(2) == Approx(123));
		REQUIRE(vec2(4) == Approx(0.1));
		vec2(0) = 12;
		REQUIRE(vec2(0) == Approx(12));
	}

	SECTION("Iterators tests TBD non-constexpr begin(), end() for now -.-"){
	}

  SECTION("Constexpr basic arithmethic between vectors"){
	  constexpr numpp::vector<double, 6> temp{7.5, -24, 43.34, 15, 2.137, 0.2};
    constexpr auto temp2 = temp + vec1;
    REQUIRE(temp2(5) == Approx(1.4));
    constexpr auto temp3 = temp2 / 2.137;
    REQUIRE(temp3(4) == Approx(1.));
    constexpr auto temp4 = vec1 - temp;
    REQUIRE(temp4(1) == Approx(28.545));
    constexpr auto temp5 = 2*temp;
    REQUIRE(temp5(0) == Approx(15.));
	  constexpr numpp::vector<double, 6, true> temp6{4.3,952.3,53.4,66.34,1.49348, -3.141516};
    constexpr auto temp8 = temp*temp6;
    REQUIRE(temp8(1,3) == Approx(-24*66.34));
    REQUIRE(temp8(4,0) == Approx(2.137*4.3));
    REQUIRE(temp8(5,5) == Approx(0.2*-3.141515));
    REQUIRE(temp8(2,2) == Approx(43.34*53.4));
	  constexpr numpp::vector<double, 3, true> temp9{2.13, -4.33, -3.34};
    constexpr auto temp10 = temp*temp9;
    REQUIRE(temp10(0,0) == Approx(7.5*2.13));
  }
}
