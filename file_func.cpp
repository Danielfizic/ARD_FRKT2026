#include <stdio.h>
#include "solve_tools.h"
#include "test_prata.h"
#include "test_prata.h"
#include "pictures_prata.h"
#include "file_func.h"

void output_key(int quantity_s, double x1, double x2);

void input_ratio_file(double* a, double* b, double* c, int* scanf_succ, int* ch, FILE* fp)
{
    assert(a);
    assert(b);
    assert(c);
    assert(fp);
    assert(scanf_succ);
    assert(a != b);
    assert(a != c);
    assert(b != c);

    *scanf_succ = fscanf(fp, "%lg %lg %lg", a, b, c);

    if (*ch != EOF)
        printf("%s%lg %lg %lg\n", LIGHT_GREEN_COL, *a, *b, *c);

    printf("%s", RESET_COL);

    assert(isinf(*a) == 0);
    assert(isinf(*b) == 0);
    assert(isinf(*c) == 0);
}

void solve_file(double a, double b, double c, double* x1, double* x2, int* quantity_s, int scanf_succ, int* ch, FILE* fp)
{
    assert(x1);
    assert(x2);
    assert(quantity_s);
    assert(x1 != x2);
    assert(ch);
    assert(fp);

    while (*ch == ' ')
        *ch = getc(fp);

    if (scanf_succ == normal_ratio && (*ch == '\n' || *ch == EOF))
        *quantity_s = num_of_solutions(a, b, c, x1, x2);
}

void output_file(int* ch, int* quantity_s, int* scanf_succ, double* x1, double* x2, FILE* fp)
{
    assert(quantity_s);
    assert(scanf_succ);
    assert(x1);
    assert(x2);
    assert(ch);

    while (*ch == ' ')
        *ch = getc(fp);

    if (*scanf_succ == normal_ratio && (*ch == '\n' || *ch == EOF))
        output_key(*quantity_s, *x1, *x2);
    else
    {
        if (*ch != '\n' && *ch != EOF)
        {
            while (*ch != '\n' && *ch != EOF)
                *ch = getc(fp);
        }

        printf("%splease, enter three numbers or \"#\"\n\n%s", PINK_COL, RESET_COL);
    }
}

