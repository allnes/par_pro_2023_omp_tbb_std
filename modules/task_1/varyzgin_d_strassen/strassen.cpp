#include <math.h>

#include <stdexcept>
#include <string>

#include "../../modules/task_1/varyzgin_d_strassen/strassen.h"

void multiplying(double *A, double *B, double *C, int n)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      C[i * n + j] = 0;
      for (int k = 0; k < n; k++)
      {
        C[i * n + j] += A[i * n + k] * B[k * n + j];
      }
    }
  }
}

void getD(double *A11, double *A22, double *res1, double *B11, double *B22,
            double *res2, double *slice, int n)
{
  for (int i = 0; i < n * n; i++)
  {
    res1[i] = A11[i] + A22[i];
    res2[i] = B11[i] + B22[i];
  }
  strassen(res1, res2, slice, n);
}
void getD1(double *A12, double *A22, double *res1, double *B21, double *B22,
            double *res2, double *slice, int n)
{
  for (int i = 0; i < n * n; i++)
  {
    res1[i] = A12[i] - A22[i];
    res2[i] = B21[i] + B22[i];
  }
  strassen(res1, res2, slice, n);
}
void getD2(double *A21, double *A11, double *res1, double *B11, double *B12,
            double *res2, double *slice, int n)
{
  for (int i = 0; i < n * n; i++)
  {
    res1[i] = A21[i] - A11[i];
    res2[i] = B11[i] + B12[i];
  }
  strassen(res1, res2, slice, n);
}
void getH1(double *A11, double *A12, double *res1, double *B22, double *slice,
            int n)
{
  for (int i = 0; i < n * n; i++)
  {
    res1[i] = A11[i] + A12[i];
  }
  strassen(res1, B22, slice, n);
}
void getH2(double *A21, double *A22, double *res1, double *B11, double *slice,
            int n)
{
  for (int i = 0; i < n * n; i++)
  {
    res1[i] = A21[i] + A22[i];
  }
  strassen(res1, B11, slice, n);
}
void getV1(double *A22, double *res1, double *B21, double *B11, double *slice,
            int n)
{
  for (int i = 0; i < n * n; i++)
  {
    res1[i] = B21[i] - B11[i];
  }
  strassen(A22, res1, slice, n);
}
void getV2(double *A11, double *res1, double *B12, double *B22, double *slice,
            int n)
{
  for (int i = 0; i < n * n; i++)
  {
    res1[i] = B12[i] - B22[i];
  }
  strassen(A11, res1, slice, n);
}

bool is_exp_of_2(int n) { return (n & (n - 1)) == 0; }

void strassen(double *A, double *B, double *C, int n)
{
  // preparing
  if (!is_exp_of_2(n))
  {
    throw std::invalid_argument("no power 2");
  }

  if (n <= 64)
  {
    multiplying(A, B, C, n);
    return;
  }

  int block_size = static_cast<int>(n * n / 4);

  // all we need
  double *A11 = new double[n * n * 2];
  double *A12 = A11 + block_size;
  double *A21 = A12 + block_size;
  double *A22 = A21 + block_size;

  double *B11 = A22 + block_size;
  double *B12 = B11 + block_size;
  double *B21 = B12 + block_size;
  double *B22 = B21 + block_size;

  double *C1 = new double[n * n + block_size * 9];
  double *C2 = C1 + block_size;
  double *C3 = C2 + block_size;
  double *C4 = C3 + block_size;

  double *D = C4 + block_size;
  double *H2 = D + block_size;
  double *V2 = H2 + block_size;
  double *V1 = V2 + block_size;
  double *H1 = V1 + block_size;
  double *D2 = H1 + block_size;
  double *D1 = D2 + block_size;

  double *res1 = D1 + block_size;
  double *res2 = res1 + block_size;

  // splitting matrices on elements
  int split = static_cast<int>(n / 2);
  for (int i = 0; i < split; i++)
  {
    for (int j = 0; j < split; j++)
    {
      A11[i * split + j] = A[i * n + j];
      A12[i * split + j] = A[i * n + split + j];
      A21[i * split + j] = A[(split + i) * n + j];
      A22[i * split + j] = A[(split + i) * n + split + j];

      B11[i * split + j] = B[i * n + j];
      B12[i * split + j] = B[i * n + split + j];
      B21[i * split + j] = B[(split + i) * n + j];
      B22[i * split + j] = B[(split + i) * n + split + j];
    }
  }

  // Shtrassen's 7 recurcieve multiplies and combining method
  getD(A11, A22, res1, B11, B22, res2, D, n / 2);
  getH2(A21, A22, res1, B11, H2, n / 2);
  getV2(A11, res1, B12, B22, V2, n / 2);
  getV1(A22, res1, B21, B11, V1, n / 2);
  getH1(A11, A12, res1, B22, H1, n / 2);
  getD2(A21, A11, res1, B11, B12, res2, D2, n / 2);
  getD1(A12, A22, res1, B21, B22, res2, D1, n / 2);
  for (int i = 0; i < (n / 2) * (n / 2); i++)
  {
    C1[i] = D[i] + V1[i] - H1[i] + D1[i];
    C2[i] = V2[i] + H1[i];
    C3[i] = H2[i] + V1[i];
    C4[i] = D[i] - H2[i] + V2[i] + D2[i];
  }

  // much arguments to 1 matrix
  for (int i = 0; i < split; i++)
  {
    for (int j = 0; j < split; j++)
    {
      C[i * n + j] = C1[i * split + j];
      C[i * n + split + j] = C2[i * split + j];
      C[(split + i) * n + j] = C3[i * split + j];
      C[(split + i) * n + split + j] = C4[i * split + j];
    }
  }

  delete[] A11;
  delete[] C1;
}
