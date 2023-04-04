// Copyright 2023 Varyzgin Dmitry
#ifndef MODULES_TASK_1_VARYZGIN_D_STRASSEN_STRASSEN_H_
#define MODULES_TASK_1_VARYZGIN_D_STRASSEN_STRASSEN_H_

void multiplying(double *a, double *b, double *c, int size);
void getD(double *A11, double *A22, double *res1, double *B11, double *B22,
            double *res2, double *slice, int n);
void getD1(double *A12, double *A22, double *res1, double *B21, double *B22,
            double *res2, double *slice, int n);
void getD2(double *A21, double *A11, double *res1, double *B11, double *B12,
            double *res2, double *slice, int n);
void getH1(double *A11, double *A12, double *res1, double *B22, double *slice,
            int n);
void getH2(double *A21, double *A22, double *res1, double *B11, double *slice,
            int n);
void getV1(double *A22, double *res1, double *B21, double *B11, double *slice,
            int n);
void getV2(double *A11, double *res1, double *B12, double *B22, double *slice,
            int n);
bool is_exp_of_2(int n);
void strassen(double *a, double *b, double *c, int size);

#endif // MODULES_TASK_1_VARYZGIN_D_STRASSEN_STRASSEN_H_