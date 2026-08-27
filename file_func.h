#ifndef _FILE_FUNC_H_
#define _FILE_FUNC_H_

#include <stdlib.h>

void solve_file(double a, double b, double c, double* x1, double* x2, int* quantity_s, int scanf_succ, int* ch, FILE* fp);
void input_ratio_file(double* a, double* b, double* c, int* scanf_succ, int* ch, FILE* fp);
void output_file(int* ch, int* quantity_s, int* scanf_succ, double* x1, double* x2, FILE* fp);

#endif
