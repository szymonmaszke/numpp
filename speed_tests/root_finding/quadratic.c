 //SOURCE FOR GSL CODE: http://www.jlekstrand.net/math/teaching/programming-course/unit-2/gsl-example/
#include "quadratic.h"

double quadratic(double x, void *params)
{
    struct quadratic_params *p;

    p = (struct quadratic_params *)params;
    return (p->a * x + p->b) * x + p->c;
}

double quadratic_deriv(double x, void *params)
{
    struct quadratic_params *p;

    p = (struct quadratic_params *)params;
    return 2.0 * p->a * x + p->b;
}

void quadratic_fdf(double x, void *params, double *y, double *dy)
{
    *y = quadratic(x, params);
    *dy = quadratic_deriv(x, params);
}
