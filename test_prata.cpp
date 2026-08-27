#include <stdio.h>
#include "solve_tools.h"
#include "test_prata.h"
#include "test_prata.h"
#include "pictures_prata.h"

test_keys run_tests()
{
    int err_eq = 0;
    test_keys test_k = e_test_good;

    test_case tests[] =
    {
    {.a = 0, .b = 0, .c = 0, .expect_quantity_s = e_inf_sol, .expect_x1 = NAN, .expect_x2 = NAN},
    {.a = 1, .b = 2, .c = 1, .expect_quantity_s = e_one_sol, .expect_x1 = -1, .expect_x2 = NAN},
    {.a = 0, .b = 0, .c = 1, .expect_quantity_s = e_no_sol, .expect_x1 = NAN, .expect_x2 = NAN},
    {.a = 0, .b = 1, .c = 0, .expect_quantity_s = e_one_sol, .expect_x1 = 0, .expect_x2 = NAN},
    {.a = 0, .b = 2, .c = -2, .expect_quantity_s = e_one_sol, .expect_x1 = 1, .expect_x2 = NAN},
    {.a = 1, .b = -100, .c = 1600, .expect_quantity_s = e_two_sol, .expect_x1 = 20, .expect_x2 = 80},
    {.a = 1, .b = -10, .c = -600, .expect_quantity_s = e_two_sol, .expect_x1 = -20, .expect_x2 = 30},
    {.a = 366, .b = 366, .c = 366, .expect_quantity_s = e_no_sol, .expect_x1 = NAN, .expect_x2 = NAN},
    {.a = -1, .b = 11, .c = 180, .expect_quantity_s = e_two_sol, .expect_x1 = -9, .expect_x2 = 20},
    {.a = 1, .b = 2, .c = -2, .expect_quantity_s = e_two_sol, .expect_x1 = -2.732050807, .expect_x2 = 0.732050807},
    {.a = 2, .b = 5, .c = 3.1, .expect_quantity_s = e_two_sol, .expect_x1 = -1.3618033988749, .expect_x2 = -1.1381966011250}
    };

    unsigned size_tests = sizeof(tests) / sizeof(tests[0]);

    for (unsigned i = 0; i < size_tests; i++)
    {
        assert(i < size_tests && i >= 0);

        run_test1(&test_k, &err_eq, tests[i]);
    }
    
    if (err_eq > 0)
        printf("%s", RED_COL);
    else
        printf("%s", GREEN_COL);

    printf("Test completed: %d errors\n\n", err_eq);
    printf("%s", RESET_COL);

    return test_k;
}

void run_test1 (test_keys* test_k, int* err_eq, test_case test)
{
    assert(err_eq);
    assert(test_k);

    double x1 = NAN, x2 = NAN;
    int quantity_s = 0;
    int ch = '\n';

    solve(test.a, test.b, test.c, &x1, &x2, &quantity_s, normal_ratio, &ch);

    bool expect_quantity =  quantity_s == test.expect_quantity_s;
    bool eq_or_nan_x1 = (iszero(x1, test.expect_x1) || (isnan(x1) && isnan(test.expect_x1)));
    bool eq_or_nan_x2 = (iszero(x2, test.expect_x2) || (isnan(x2) && isnan(test.expect_x2)));

    if (expect_quantity && eq_or_nan_x1 && eq_or_nan_x2)
        return;

    fprintf(stderr, "%sTest FAILED:\n"                                         //если есть ошибка
           "          num of solutions         x1          x2\n"
           "got:      %16d %9lg %9lg\n"
           "expected: %16d %9lg %9lg\n\n%s",
           RED_COL, test.expect_quantity_s, test.expect_x1, test.expect_x2,
           quantity_s, x1, x2, RESET_COL);

    *test_k = e_test_bad;
    *err_eq = *err_eq + 1;
}