#ifndef _TEST_PRATA_H_
#define _TEST_PRATA_H_

enum test_keys  {e_test_bad, e_test_good};

struct test_case
{
    double a, b, c;
    int expect_quantity_s;
    double expect_x1, expect_x2;
};

void run_test1          (test_keys* test_k, int* err_eq, test_case test);
test_keys run_tests     ();

#endif