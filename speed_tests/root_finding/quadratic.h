 //SOURCE FOR GSL CODE: http://www.jlekstrand.net/math/teaching/programming-course/unit-2/gsl-example/
#ifndef __EXAMPLES_LIBGSL_QUADRATIC_H__
#define __EXAMPLES_LIBGSL_QUADRATIC_H__

struct quadratic_params {
    double a, b, c;
};

/* Returns the value of the quadratic at x */
double quadratic(double x, void *params);

/* Returns the derivative of the quadratic at x */
double quadratic_deriv(double x, void *params);

/* Evaluates both the quadratic and its derivative at x and stores the
 * value in *y and the derivative in *dy. */
void quadratic_fdf(double x, void *params, double *y, double *dy);

#endif /* !defined __EXAMPLES_LIBGSL_QUADRATIC_H__ */
