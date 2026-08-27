#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "solve_tools.h"
#include "pictures_prata.h"
#include "test_prata.h"
#include "file_func.h"

void pager              (void);
void input_ratio        (double* a, double* b, double* c, int* scanf_succ);
void output             (int* ch, int* quantity_s, int* scanf_succ, double* x1, double* x2);
void output_key         (int quantity_s, double x1, double x2);
void input_ratio_file   (double* a, double* b, double* c, int* scanf_succ, int* ch, FILE* fp);
void solve_file         (double a, double b, double c, double* x1, double* x2, int* quantity_s, int scanf_succ, int* ch, FILE* fp);

int main(void)
{
    pager();

    double a = NAN, b = NAN, c = NAN;
    double x1 = NAN, x2 = NAN;
    int scanf_succ = 0;
    int ch = 0;
    int quantity_s = 0;
    test_keys test_k = e_test_good;

    test_k = run_tests();
    if (test_k == e_test_bad)
        return -1;

    printf("Enter \"F\" to start file input (inputfile.txt) or anything to continue\n");
    if (getchar() == 'F')
    {
        FILE* fp = fopen("inputfile.txt", "r");

        input_ratio_file(&a, &b, &c, &scanf_succ, &ch, fp);

        while (ch != EOF)
        {
            ch = getc(fp);

            solve_file(a, b, c, &x1, &x2, &quantity_s, scanf_succ, &ch, fp);

            output_file(&ch, &quantity_s, &scanf_succ, &x1, &x2, fp);

            input_ratio_file(&a, &b, &c, &scanf_succ, &ch, fp);
        }

        fclose(fp);
    }

    while (getchar() != '\n')
        continue;

    input_ratio(&a, &b, &c, &scanf_succ);

    while ((ch = getchar()) != '#')
    {
        solve(a, b, c, &x1, &x2, &quantity_s, scanf_succ, &ch);

        output(&ch, &quantity_s, &scanf_succ, &x1, &x2);

        input_ratio(&a, &b, &c, &scanf_succ);
    }

    picture();

    return 0;
}

void pager(void)
{
    printf("%s%s# Square equations solver\n", BLUE_COL, BLINK_COL);
    printf("# (c) Daniel (ARD), 2026\n\n%s",  RESET_COL);
}

void input_ratio(double* a, double* b, double* c, int* scanf_succ)
{
    assert(a);
    assert(b);
    assert(c);
    assert(scanf_succ);
    assert(a != b);
    assert(a != c);
    assert(b != c);

    printf("%senter a, b and c or \"#\" to quit:\n%s", BLUE_COL, LIGHT_GREEN_COL);
    *scanf_succ = scanf("%lg %lg %lg", a, b, c);
    printf("%s", RESET_COL);

    assert(isinf(*a) == 0);
    assert(isinf(*b) == 0);
    assert(isinf(*c) == 0);
}

void output(int* ch, int* quantity_s, int* scanf_succ, double* x1, double* x2)
{
    assert(quantity_s);
    assert(scanf_succ);
    assert(x1);
    assert(x2);
    assert(ch);

    while (*ch == ' ')
        *ch = getchar();

    if (*scanf_succ == normal_ratio && *ch == '\n')
        output_key(*quantity_s, *x1, *x2);
    else
    {
        if (*ch != '\n')
        {
            while ((*ch = getchar()) != '\n')
                continue;
        }

        printf("%splease, enter three numbers or \"#\"\n\n%s", PINK_COL, RESET_COL);
    }
}

void output_key(int quantity_s, double x1, double x2)
{
    printf("%s", GREEN_COL);

    switch(quantity_s)
    {
        case e_no_sol:  printf("The equation has no solutions\n\n");
                break;

        case e_one_sol: printf("The equation has one solution: %lg\n\n", x1);
                break;

        case e_two_sol: printf("The equation has two solutions: x1 = %lg and x2 = %lg\n\n", x1, x2);
                break;

        case e_inf_sol: printf("Any number\n\n");
                break;
        default: fprintf(stderr, "%sERROR: switch key quantity_s not defined\n\n", RED_COL);
    }

    printf("%s", RESET_COL);
}