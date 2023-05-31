// Copyright 2023 Bykova Alekandra
#ifndef MODULES_TASK_3_BYKOVA_A_MULTIPLY_MATRIX_FOX_MULTIPLY_MATRIX_FOX_H_
#define MODULES_TASK_3_BYKOVA_A_MULTIPLY_MATRIX_FOX_MULTIPLY_MATRIX_FOX_H_
#include <vector>
#define NTHREADS 4

typedef std::vector<std::vector<double>> matrix;
typedef unsigned int uint;
bool canMultiplicate(const matrix &a, const matrix &b);
void prepareOutMatrix(matrix *matrixOut, uint sizeRow, uint sizeCol);
bool initMatrixRand(matrix *a, uint sizeRow, uint sizeCol);
bool simpleMaxtrixMultiply(const matrix &a, const matrix &b, matrix *out);

bool isSquareMatrix(const matrix &a, const matrix &b);
bool algFoxMatrixMultiplySeq(const matrix &a, const matrix &b, matrix *out);
bool algFoxMatrixMultiplyPar(const matrix &a, const matrix &b, matrix *out);


#endif  // MODULES_TASK_3_BYKOVA_A_MULTIPLY_MATRIX_FOX_MULTIPLY_MATRIX_FOX_H_
