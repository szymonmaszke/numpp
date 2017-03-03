#include "../catch.hpp"
#include "../../differentiation/central.hpp"

#if (defined(__GNUC__) || defined(__GNUG__)) && !(defined(__clang__) || defined(__INTEL_COMPILER))
  TEST_CASE(
      "central finite difference tests",
      "[differentiation][central]"
      ){

    class example_function{
      public:
        constexpr double operator()(const double x) const{
          return std::pow(std::pow(x,3.33)/(x+123),4)
            /std::hypot(std::sqrt(x+12.1) ,std::pow(x-3.14, 2));
        }
    };
    constexpr example_function f{};

    SECTION("basic result tests"){
      constexpr auto result1 = numpp::derivative::central(f, 2.53, 0.00001);
      constexpr auto result2 = numpp::derivative::central(f, 2.53);
      SECTION("correct results"){
        REQUIRE(result1 == Approx(0.0012835));
      }
      SECTION("set h vs auto h"){
        REQUIRE(result1 == Approx(result2));
      }
    }

  }
#endif
