 //SOURCE FOR GSL CODE: http://www.jlekstrand.net/math/teaching/programming-course/unit-2/gsl-example/
#include<iostream>
#include<chrono>
#include"../../root_finding/bisection.hpp"
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_roots.h>

#include "quadratic.h"

#define MAX_ITERATIONS 100

class Function{
	public:
		constexpr Function()=default;
		constexpr double operator()(const double x){
			return x*x -3;
		}
};

int main(){
  //NUMPP BISECTION METHOD
  auto begin_numpp = std::chrono::high_resolution_clock::now();
	constexpr auto zero_epsilon = numpp::root_finding::bisection(Function{}, 1., 2.);
  auto end_numpp = std::chrono::high_resolution_clock::now();
  std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end_numpp-begin_numpp).count() << "ns" << std::endl;
	std::cout << "numpp zero: " << zero_epsilon << std::endl;

  //GSL BISECTION METHOD
  auto begin_gsl= std::chrono::high_resolution_clock::now();
  int status;
  int i;
  const gsl_root_fsolver_type *solver_type;
  gsl_root_fsolver *solver;
  gsl_function F;
  double r;

  /* We want to solve x^2 - 3 */
  struct quadratic_params params = { 1.0, 0.0, -3.0 };
  /* On the interval [1, 2] */
  double x_lo = 1.0, x_hi = 2.0;

  /* Set up the function */
  F.function = &quadratic;
  F.params = &params;

  /* Allocate a bisection solver and set it to use F */
  solver_type = gsl_root_fsolver_bisection;
  solver = gsl_root_fsolver_alloc(solver_type);
  gsl_root_fsolver_set(solver, &F, x_lo, x_hi);

  status = GSL_CONTINUE;
  for (i = 1; i <= MAX_ITERATIONS && status == GSL_CONTINUE; ++i) {
      /* iterate one step of the solver */
      status = gsl_root_fsolver_iterate(solver);
      if (status != GSL_SUCCESS)
          break;

      /* get the solver's current best solution and bounds */
      r = gsl_root_fsolver_root(solver);
      x_lo = gsl_root_fsolver_x_lower(solver);
      x_hi = gsl_root_fsolver_x_upper(solver);

      /* Check to see if the solution is within 0.001 */
      status = gsl_root_test_interval(x_lo, x_hi, 0, 0.001);
      if (status == GSL_SUCCESS)
        break;

  }

  /* Free the solver */
  gsl_root_fsolver_free(solver);
  auto end_gsl = std::chrono::high_resolution_clock::now();
  std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end_gsl-begin_gsl).count() << "ns" << std::endl;
  std::cout << "GSL zero: " << r << std::endl;
}

