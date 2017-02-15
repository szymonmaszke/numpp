#include "../../catch.hpp"
#include "../../../structures/vector/vector_structure.hpp"

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
}
