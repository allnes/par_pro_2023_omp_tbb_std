// Copyright 2023 Pikin Ilya
#include "../../../modules/task_1/pikin_i_sparse_matrix_mult/sparse_matrix_mult.h"

CRSMatrix::CRSMatrix(const std::vector<std::vector<std::complex<double>>>& M) {
  n = M.size();
  nz = 0;
  if (n != 0) {
    rowIndex.resize(n + 1ll);
    rowIndex[0] = 0;
  }
  for (int i = 0; i < n; i++) {
    rowIndex[i + 1ll] = rowIndex[i];
    for (int j = 0; j < n; j++) {
      std::complex<double> v = M[i][j];
      if (abs(v.real()) >= EPSILON || abs(v.imag()) >= EPSILON) {
        value.push_back(v);
        column.push_back(j);
        nz++;
        rowIndex[i + 1ll]++;
      }
    }
  }
}

CRSMatrix::CRSMatrix(int n, int nz, const std::vector<std::complex<double>>& v,
                     const std::vector<int>& c, const std::vector<int>& rI)
    : n(n), nz(nz), value(v), column(c), rowIndex(rI) {}

void CRSMatrix::printData() {
  std::cout << "N = " << n << std::endl;
  std::cout << "NZ = " << nz << std::endl;
  std::cout << "Values: \n";
  for (auto el : value) {
    std::cout << el << " ";
  }
  std::cout << std::endl << "Columns: \n";
  for (auto el : column) {
    std::cout << el << " ";
  }
  std::cout << std::endl << "Row indexes: \n";
  for (auto el : rowIndex) {
    std::cout << el << " ";
  }
  std::cout << std::endl;
}

void CRSMatrix::printAsMatrix() {
  if (n < 1) {
    throw std::string("The dimension of the matrix is less than one!");
  }
  int ind1, ind2, currentInd = 0;
  for (int i = 0; i < n; i++) {
    ind1 = rowIndex[i];
    ind2 = rowIndex[i + 1ll];
    for (int j = 0; j < n; j++) {
      if (ind1 < ind2 && currentInd < ind2 && column[currentInd] == j) {
        std::cout << value[currentInd] << " ";
        // std::cout << value[currentInd].real()<<"+(" <<
        // value[currentInd].imag() << "i) ";

        currentInd++;
      } else {
        std::cout << "(0, 0) ";
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

bool CRSMatrix::operator==(const CRSMatrix& M) const {
  if (this == &M) {
    return true;
  }
  if (n != M.n || nz != M.nz) return false;

  if (value.size() != M.value.size() || column.size() != M.column.size() ||
      rowIndex.size() != M.rowIndex.size())
    return false;

  if (value.size() != column.size()) {
    throw std::string("Incorrect data!");
  }
  for (int i = 0; i < value.size(); i++) {
    std::complex<double> delta = value[i] - M.value[i];

    if (abs(delta.real()) > EPSILON || abs(delta.imag()) > EPSILON ||
        column[i] != M.column[i])
      return false;
  }

  for (int i = 0; i < rowIndex.size(); i++) {
    if (rowIndex[i] != M.rowIndex[i]) return false;
  }
  return true;
}

CRSMatrix getTransposed(const CRSMatrix& A) {
  if (A.n < 1) {
    throw std::string("The dimensions of the matrices are less than one!");
  }
  CRSMatrix AT;
  AT.n = A.n;
  AT.nz = A.nz;
  // Resizing and initialization empty vectors by zero
  AT.value.resize(AT.nz);
  AT.column.resize(AT.nz);
  AT.rowIndex.resize(AT.n + 1ll);

  // Counting the number of elements in each row of matrix A
  // and storing the values in AT.rowIndex (with a shift)
  for (int i = 0; i < AT.nz; i++) {
    AT.rowIndex[A.column[i] + 1ll]++;
  }

  // Counting the indexes of the beginning of rows
  int s = 0;
  for (int i = 1; i <= AT.n; i++) {
    int tmp = AT.rowIndex[i];
    AT.rowIndex[i] = s;
    s += tmp;
  }

  // Saving matrix values in the correct location
  for (int i = 0; i < A.n; i++) {
    int j1 = A.rowIndex[i];
    int j2 = A.rowIndex[i + 1ll];
    int col = i;  // Column in AT <-> row in A

    for (int j = j1; j < j2; j++) {
      std::complex<double> v = A.value[j];
      int RIndex = A.column[j];  // Row in AT

      // IIndex is a current index in AT.value
      int IIndex = AT.rowIndex[RIndex + 1ll];
      AT.value[IIndex] = v;
      AT.column[IIndex] = col;
      AT.rowIndex[RIndex + 1ll]++;
    }
  }

  return AT;
}

CRSMatrix getProductSeq(const CRSMatrix& A, const CRSMatrix& B) {
  if (A.n != B.n) {
    throw std::string("The dimensions of the matrices are not equal!");
  }
  if (A.n < 1) {
    throw std::string("The dimensions of the matrices are less than one!");
  }
  if (A.nz == 0 || B.nz == 0) {
    CRSMatrix C;
    C.n = A.n;
    C.rowIndex.resize(C.n + 1, 0);
    return C;
  }

  int n = A.n;
  int nz = 0;
  std::vector<std::complex<double>> value;
  std::vector<int> column;
  std::vector<int> rowIndex(n + 1ll);

  CRSMatrix BT = getTransposed(B);

  std::vector<int> temp(n);
  rowIndex[0] = 0;
  for (int i = 0; i < n; i++) {
    for (int k = 0; k < n; k++) temp[k] = -1;

    int ind1 = A.rowIndex[i];
    int ind2 = A.rowIndex[i + 1];
    for (int j = ind1; j < ind2; j++) {
      int col = A.column[j];
      temp[col] = j;
    }
    for (int j = 0; j < n; j++) {
      std::complex<double> sum(0, 0);
      int ind3 = BT.rowIndex[j];
      int ind4 = BT.rowIndex[j + 1];
      for (int k = ind3; k < ind4; k++) {
        int BTcol = BT.column[k];
        int Aind = temp[BTcol];
        if (Aind != -1) {
          sum += A.value[Aind] * BT.value[k];
        }
      }
      if (abs(sum.real()) >= EPSILON || abs(sum.imag()) >= EPSILON) {
        column.push_back(j);
        value.push_back(sum);
        nz++;
      }
    }
    rowIndex[i + 1] = nz;
  }
  CRSMatrix C;
  C.n = n;
  C.nz = nz;
  C.column = move(column);
  C.value = move(value);
  C.rowIndex = move(rowIndex);

  return C;
}

CRSMatrix getRandCRSMatrix(int n, int cntInRow) {
  if (cntInRow <= 0 || n <= 0) {
    throw std::string("n and cntInRow must be greater than zero!");
  }
  if (cntInRow > n) {
    cntInRow = n;
  }
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distIndex(0, n - 1);
  std::uniform_real_distribution<> distValue(-10.0, 10.0);

  CRSMatrix Result;
  Result.n = n;
  Result.nz = n * cntInRow;
  Result.value.resize(n * cntInRow);
  Result.column.resize(n * cntInRow);
  Result.rowIndex.resize(n + 1);

  int curInd = 0;
  for (int i = 0; i < n; i++) {
    std::set<int> s;
    while (s.size() < cntInRow) {
      int newIndex = distIndex(gen);
      s.insert(newIndex);
    }
    for (auto it = s.begin(); it != s.end(); it++) {
      Result.column[curInd] = *it;
      std::complex<double> newValue(distValue(gen), distValue(gen));
      Result.value[curInd] = newValue;
      curInd++;
    }
  }
  int c = 0;
  for (int i = 0; i < n + 1; i++) {
    Result.rowIndex[i] = c;
    c += cntInRow;
  }
  return CRSMatrix(Result);
}
