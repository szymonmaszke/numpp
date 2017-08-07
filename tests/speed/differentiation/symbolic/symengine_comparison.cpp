#include<chrono>
#include<typeinfo>
#include<random>

#include"symengine/functions.h"
#include"symengine/eval_double.h"
#include"symengine/add.h"
#include"symengine/pow.h"
#include"symengine/real_double.h"
#include"symengine/basic.h"

#include"../../../../differentiation/symbolic.hpp"

using SymEngine::RCP;
using SymEngine::Symbol;
using SymEngine::symbol;
using SymEngine::real_double;
namespace nds = numpp::differentiation::symbolic;

int main(int argc, char** argv){
  //CHECK ARGUMENTS
  if(argc!=4){
    std::cerr << "Wrong number of arguments! \nCorrect run: prog TESTS LOWER_ARGUMENT UPPER_ARGUMENT " << std::endl;
    return 1;
  }

  //PARSE ARGUMENTS
  const std::size_t TEST_CASES = atoi(argv[1]);
  const double LOWER_BOUND = atof(argv[2]);
  const double UPPER_BOUND = atof(argv[3]);

  //CHECK PARSING
  if(TEST_CASES == 0){
    std::cerr << "0 tests cannot be run. Provide integer of 1 or more" << std::endl;
    return 1;
  }

  //CREATE RANDOM DEVICES
  std::uniform_real_distribution<double> dist(LOWER_BOUND, UPPER_BOUND);
  std::default_random_engine engine(std::random_device{}());

  //MEASURE OBJECT CREATION TIME
  auto sym_start = std::chrono::system_clock::now();
  const auto x = SymEngine::symbol("x");
  const auto y = SymEngine::symbol("y");

  //MEASURE SYMBOLIC DIFFERENTIATION TIME
  auto sym_create_end = std::chrono::system_clock::now();
  const auto derivative = mul(exp(add(sin(x),cos(y))), log(x))->diff(x)->diff(y)->diff(x)->diff(y);

  //MEASURE EVALUATION OF DERIVATIVES FOR RANDOM NUMBERS TEST_CASES TIMES
  auto sym_derivative_end = std::chrono::system_clock::now();
  auto sym_value = eval_double(*(derivative->subs({{x, real_double(dist(engine))}, {y, real_double(dist(engine))}})));
  for(std::size_t i=0; i<TEST_CASES-1; ++i)
    sym_value = eval_double(*(derivative->subs({{x, real_double(dist(engine))}, {y, real_double(dist(engine))}})));
  auto sym_end = std::chrono::system_clock::now();

  //PRINT THE RESULTS
  std::cout << "---------SYMENGINE-------\n\n";
  std::cout << "Last result of derivatives evaluations: " << sym_value << std::endl;
  std::cout << "Two variables creation time in nanoseconds: " << std::chrono::duration_cast<std::chrono::nanoseconds>(sym_create_end-sym_start).count() << std::endl;
  std::cout << "Derivative creation time in nanoseconds: " << std::chrono::duration_cast<std::chrono::nanoseconds>(sym_derivative_end-sym_create_end).count() << std::endl;
  std::cout << TEST_CASES << " derivatives evaluated in nanoseconds: " << std::chrono::duration_cast<std::chrono::nanoseconds>(sym_end-sym_derivative_end).count() << std::endl;
  auto per_derivative_symeng = std::chrono::duration_cast<std::chrono::nanoseconds>(sym_end-sym_derivative_end).count()/TEST_CASES;
  std::cout << "Average time per one derivative evaluation in nanoseconds: " << per_derivative_symeng << std::endl;
  std::cout << "Overall time in nanoseconds: " << std::chrono::duration_cast<std::chrono::nanoseconds>(sym_end-sym_start).count() << "\n\n";

  //MEASURE FUNCTION CREATION TIME
  auto numpp_start = std::chrono::system_clock::now();
  using Function = decltype(exp(sin(nds::x<0>{})+cos(nds::x<1>{})) * log(nds::x<0>{}));

  //MEASURE SYMBOLIC DIFFERENTIATION TIME
  auto function_creation = std::chrono::system_clock::now();
  using Derivative = nds::differentiate<Function, 4>::with_respect_to<0,1,0,1>;


  //MEASURE EVALUATION OF DERIVATIVES FOR RANDOM NUMBERS TEST_CASES TIMES
  auto derivative_creation = std::chrono::system_clock::now();
  auto numpp_value = Derivative::calculate(std::array<double, 2>{dist(engine),dist(engine)});
  for(std::size_t i=0; i<TEST_CASES-1; ++i)
    numpp_value = Derivative::calculate(std::array<double, 2>{dist(engine),dist(engine)});
  auto numpp_end = std::chrono::system_clock::now();
  std::cout << "----------NUMPP----------\n\n";
  std::cout << "Last result of derivatives evaluations: " << numpp_value << std::endl;
  std::cout << "Function creation time in nanoseconds: " << std::chrono::duration_cast<std::chrono::nanoseconds>(function_creation-numpp_start).count() << std::endl;
  std::cout << "Derivative creation time in nanoseconds: " << std::chrono::duration_cast<std::chrono::nanoseconds>(derivative_creation-function_creation).count() << std::endl;
  std::cout << TEST_CASES << " derivatives evaluated in nanoseconds: " << std::chrono::duration_cast<std::chrono::nanoseconds>(numpp_end-derivative_creation).count() << std::endl;
  auto per_derivative_numpp = std::chrono::duration_cast<std::chrono::nanoseconds>(numpp_end-derivative_creation).count()/TEST_CASES;
  std::cout << "Average time per one derivative evaluation in nanoseconds: " << per_derivative_numpp << std::endl;
  std::cout << "Overall time in nanoseconds: " << std::chrono::duration_cast<std::chrono::nanoseconds>(numpp_end-numpp_start).count() << std::endl;
  std::cout << "\nCHECK RESULT OF EVALUATION:" << std::endl;


  //IF NUMPP ISN'T 5x FASTER RETURN ERROR
  if(per_derivative_symeng<per_derivative_numpp*5)
    return 1;
  return 0;

}
