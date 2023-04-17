// Copyright 2023 Nikitin Aleksandr
#ifndef MODULES_TASK_1_NIKITIN_A_STRASSEN_STRASSEN_H_
#define MODULES_TASK_1_NIKITIN_A_STRASSEN_STRASSEN_H_

void strassen(double* a, double* b, double* c, int size);
void naive_mult(double* a, double* b, double* c, int size);
bool is_exp_of_2(int n);
void get_p1(double* a11, double* a22, double* res1, double* b11, double* b22,
            double* res2, double* slice1, int size);
void get_p2(double* a21, double* a22, double* res1, double* b11, double* slice2,
            int size);
void get_p3(double* a11, double* res1, double* b12, double* b22, double* slice3,
            int size);
void get_p4(double* a22, double* res1, double* b21, double* b11, double* slice4,
            int size);
void get_p5(double* a11, double* a12, double* res1, double* b22, double* slice5,
            int size);
void get_p6(double* a21, double* a11, double* res1, double* b11, double* b12,
            double* res2, double* slice6, int size);
void get_p7(double* a12, double* a22, double* res1, double* b21, double* b22,
            double* res2, double* slice7, int size);

#endif  // MODULES_TASK_1_NIKITIN_A_STRASSEN_STRASSEN_H_
