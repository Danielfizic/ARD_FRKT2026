#include <stdio.h>
#include "solve_tools.h"
#include "test_prata.h"

void solve(double a, double b, double c, double* x1, double* x2, int* quantity_s, int scanf_succ, int* ch)
{
    assert(x1);
    assert(x2);
    assert(quantity_s);
    assert(x1 != x2);
    assert(ch);

    while (*ch == ' ')
        *ch = getchar();

    if (scanf_succ == normal_ratio && *ch == '\n')
        *quantity_s = num_of_solutions(a, b, c, x1, x2);
}

sol_eq num_of_solutions(double a, double b, double c, double* x1, double* x2)
{
    assert(x1);
    assert(x2);
    assert(x1 != x2);

    if (iszero(a, 0))
        return a_is_zero(b, c, x1, x2);
    else
        return a_is_not_zero(a, b, c, x1, x2);
}

sol_eq a_is_zero(double b, double c, double* x1, double* x2)
{
    assert(x1);
    assert(x2);

    if (iszero(b, 0))
    {
        *x1 = NAN;
        *x2 = NAN;

        return b_and_a_is_zero(c);
    }

    else
    {
        if (iszero(c, 0))
            *x1 = 0;
        else
            *x1 = - c / b;

        *x2 = NAN;

        return e_one_sol;
    }
}

sol_eq b_and_a_is_zero(double c)
{
    if (iszero(c, 0))
        return e_inf_sol;
    else
        return e_no_sol;
}

sol_eq a_is_not_zero(double a, double b, double c, double* x1, double* x2)
{
    assert(x1);
    assert(x2);
    assert(x1 != x2);

    double d = b * b - 4 * a * c;

    if (iszero(d, 0))
        return d_is_zero(a, b, c, x1, x2);

    else if (d > 0)
        return d_positive(a, b, c, x1, x2, d);
    
    else if (d < 0)
    {
        *x1 = NAN;
        *x2 = NAN;
        
        return e_no_sol;
    }

    *x1 = NAN;
    *x2 = NAN;

    printf("SOLVE ERROR (a_is_not_zero)");

    return e_error_sol;
}

sol_eq d_is_zero(double a, double b, double c, double* x1, double* x2)
{
    if (iszero(b, 0))
            *x1 = 0;
    else
        *x1 = - b / 2 / a;
    *x2 = NAN;

    return e_one_sol;
}

sol_eq d_positive(double a, double b, double c, double* x1, double* x2, double d)
{
    if (a > 0)
    {
        *x1 = (- b - sqrt(d)) / 2 / a;
        *x2 = (- b + sqrt(d)) / 2 / a;
    }
    else
    {
        *x1 = (- b + sqrt(d)) / 2 / a;
        *x2 = (- b - sqrt(d)) / 2 / a;
    }

    return e_two_sol;
}

bool iszero(double x, double y)
{
    double delta = fabs(x - y);

    if (delta <= eps)
        return true;

    return false;
}
