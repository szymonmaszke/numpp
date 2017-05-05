#include "../../utilities/catch.hpp"
#include "numpp/structures/vector/vector_operations.hpp"
#include "../../../structures/matrix_vector_operations.hpp"

TEST_CASE(
		"vector matrix normal multiplication test",
		"[structure][vector][normal][matrix][compile-time]"
){
	constexpr numpp::vector<int, 6, false> vector{3, 4, 123, 25, 0, 1};
	constexpr numpp::matrix::normal<double, 3, 6> matrix{
    0, -12, 1244.1337, 25.33, .1, .243125,
    14.3, 32.5351, -4892, 514.3, 0.4515, 9696,
    593.51, -769.34, 0, 0, 589.00024, -12.37
  };

	constexpr auto result = matrix*vector;
	REQUIRE(result(0) == Approx(153613.93822500002));
	REQUIRE(result(1) == Approx(-578989.4596));
	REQUIRE(result(2) == Approx(-1309.2));
	REQUIRE(result.size() == 3);

}
