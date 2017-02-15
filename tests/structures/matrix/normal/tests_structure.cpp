#include "../../../catch.hpp"
#include "../../../../structures/matrixes/matrixes.hpp"

TEST_CASE(
		"normal matrix basic functionality tests",
		"[structures][matrix][normal][compile-time]"
){
	constexpr int ROWS = 4, COLUMNS = 5;
	constexpr numpp::matrix::normal<double, ROWS, COLUMNS> mat_a{
		1.2, -4.5, 12412.3, 12512., 294.2352,
		2, 5.35, -412.3, 12, 0,
		-34, 0, 0, 0, 4.5,
		3, 1.3, 1.7, 0, 0
	};

	numpp::matrix::normal<double, ROWS, COLUMNS> mat_b{};

	SECTION("comparing two different matrixes"){
		REQUIRE_FALSE(mat_a == mat_b);
		SECTION("copying one matrix into another (equal?)"){
			mat_b = mat_a;
			REQUIRE(mat_a == mat_b);
		}
	}

	SECTION("constexpr copy-constructor"){
		constexpr numpp::matrix::normal<double, ROWS, COLUMNS> mat_c{mat_a};
		REQUIRE(mat_c == mat_a);
	}

	SECTION("size functions"){
		REQUIRE(mat_a.size() == 20);
		REQUIRE(mat_a.max_size() == mat_a.size());
		REQUIRE(mat_a.row_size() == ROWS);
		REQUIRE(mat_a.column_size() == COLUMNS);
	}

	SECTION("access operator()"){
		SECTION("constexpr normal matrix access")
			REQUIRE(mat_a(0,1) == Approx(-4.5));
			REQUIRE(mat_a(1,0) == Approx(2.));
			REQUIRE(mat_a(1,4) == Approx(0));
			REQUIRE(mat_a(2,4) == Approx(4.5));
			REQUIRE(mat_a(3,4) == Approx(0));
			REQUIRE(mat_a(3,4) == Approx(0));
		SECTION("normal matrix access"){
			REQUIRE(mat_b(2,3) == Approx(0));
			SECTION("normal matrix assigining"){
				mat_b(0,0) = 5.5;
				REQUIRE(mat_b(0,0) == Approx(5.5));
			}
		}
	}
}
