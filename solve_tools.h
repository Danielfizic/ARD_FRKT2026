#ifndef _SOLVE_TOOLS_H_
#define _SILVE_TOOLS_H_

#include <assert.h>
#include <math.h>

enum sol_eq     {e_error_sol = -1, e_no_sol, e_one_sol, e_two_sol, e_inf_sol};

const int normal_ratio = 3;
const double eps       = 1e-8;

void solve              (double a, double b, double c, double* x1, double* x2, int* quantity_s, int scanf_succ, int* ch);
sol_eq num_of_solutions (double a, double b, double c, double* x1, double* x2);
sol_eq a_is_zero        (double b, double c, double* x1, double* x2);
sol_eq b_and_a_is_zero  (double c);
sol_eq a_is_not_zero    (double a, double b, double c, double* x1, double* x2);
sol_eq d_is_zero        (double a ,double b, double c, double* x1, double* x2);
sol_eq d_positive       (double a, double b, double c, double* x1, double* x2, double d);
bool iszero             (double x, double y);

#endif