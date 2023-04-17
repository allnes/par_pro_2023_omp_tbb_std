// Copyright 2023 Pashina Alina
#include <gtest/gtest.h>

#include <iostream>
#include <random>
#include <string>
#include <vector>

class CRSMatrix {
 public:
  int numRow, numCol;
  std::vector<double> valueCRS;
  std::vector<int> colsCRS;
  std::vector<int> pointerCRS;

  CRSMatrix(int numC, int numR, const std::vector<double>& myVal,
            const std::vector<int>& myColu, const std::vector<int>& myPointer)
      : valueCRS(myVal),
        numCol(numC),
        colsCRS(myColu),
        numRow(numR),
        pointerCRS(myPointer) {}
  explicit CRSMatrix(int numC = 0, int numR = 0) {
    numCol = numC;
    numRow = numR;
  }
  explicit CRSMatrix(std::vector<std::vector<double>> matr) {
    int indexCounter = 0;
    numRow = matr.size();
    numCol = matr[0].size();
    pointerCRS.push_back(indexCounter);
    for (int r = 0; r < numRow; r++) {
      for (int c = 0; c < numCol; c++) {
        if (matr[r][c] != 0) {
          valueCRS.push_back(matr[r][c]);
          indexCounter++;
          colsCRS.push_back(c);
        }
      }
      pointerCRS.push_back(indexCounter);
    }
  }
  bool operator==(const CRSMatrix& matr) const {
    if ((valueCRS == matr.valueCRS) && (numCol == matr.numCol) &&
        (colsCRS == matr.colsCRS) && (numRow == matr.numRow) &&
        (pointerCRS == matr.pointerCRS)) {
      return true;
    }
    return false;
  }
  CRSMatrix MatrixTransp() {
    CRSMatrix matr;
    std::vector<std::vector<int>> locCVec(numCol);
    std::vector<std::vector<double>> locVecVal(numCol);
    matr.numCol = numRow;
    int elemCounter = 0;
    matr.numRow = numCol;

    for (int r = 0; r < numRow; r++) {
      for (int ind = pointerCRS[r]; ind < pointerCRS[r + 1]; ind++) {
        int colInd = colsCRS[ind];
        locCVec[colInd].push_back(r);
        locVecVal[colInd].push_back(valueCRS[ind]);
      }
    }
    matr.pointerCRS.push_back(elemCounter);
    for (int col = 0; col < numCol; col++) {
      for (size_t ktmp = 0; ktmp < locCVec[col].size(); ktmp++) {
        matr.colsCRS.push_back(locCVec[col][ktmp]);
        matr.valueCRS.push_back(locVecVal[col][ktmp]);
      }
      elemCounter += locCVec[col].size();
      matr.pointerCRS.push_back(elemCounter);
    }
    return matr;
  }
  CRSMatrix MatrixMult(CRSMatrix matr) {
    if (matr.numCol != numCol) {
      throw std::runtime_error("Wrong matrix sizes!Change rows \n");
    }
    std::vector<int> finColumn, finPointer;
    std::vector<double> finValue;
    int nRowZero = 0;
    finPointer.push_back(nRowZero);
    int finNumRows = numRow;
    int finNumCols = matr.numCol;
    for (int r1 = 0; r1 < numRow; r1++) {
      nRowZero = 0;
      for (int r2 = 0; r2 < matr.numRow; r2++) {
        int firstStart = pointerCRS[r1];
        int secondStart = matr.pointerCRS[r2];
        double localSum = 0;
        while (((matr.pointerCRS[r2 + 1] - 1) >= secondStart) &&
               ((pointerCRS[r1 + 1] - 1) >= firstStart)) {
          if (colsCRS[firstStart] == matr.colsCRS[secondStart]) {
            localSum += (valueCRS[firstStart] * matr.valueCRS[secondStart]);
            firstStart = firstStart + 1;
            secondStart = secondStart + 1;
          } else {
            if (colsCRS[firstStart] < matr.colsCRS[secondStart]) {
              firstStart = firstStart + 1;
            } else {
              secondStart = secondStart + 1;
            }
          }
        }
        if (localSum != 0) {
          nRowZero = nRowZero + 1;
          finColumn.push_back(r2);
          finValue.push_back(localSum);
        }
      }
      finPointer.push_back(nRowZero + finPointer[r1]);
    }

    CRSMatrix res(finNumCols, finNumRows, finValue, finColumn, finPointer);
    return res;
  }
};

std::vector<std::vector<double>> fillZero(int cols, int rows) {
  std::vector<std::vector<double>> res(rows);
  for (int m = 0; m < rows; m++) {
    for (int n = 0; n < cols; n++) {
      res[m].push_back(0);
    }
  }
  return res;
}
std::vector<std::vector<double>> createRandomMatrix(int cols, int rows,
                                                    double perc) {
  if (perc < 0 || perc > 1) {
    throw std::runtime_error("Wrong density \n");
  }
  std::random_device mydev;
  std::vector<std::vector<double>> res = fillZero(cols, rows);
  std::mt19937 gen(mydev());
  std::uniform_real_distribution<double> genP{0.0, 1.0};
  std::uniform_real_distribution<double> genVal{0.0, 25.0};
  for (int ro = 0; ro < rows; ro++) {
    for (int col = 0; col < cols; col++) {
      if (genP(gen) <= perc) {
        res[ro][col] = genVal(gen);
      }
    }
  }
  return res;
}

std::vector<std::vector<double>> multiplyVecMatrix(
    std::vector<std::vector<double>> myFirstMatrix,
    std::vector<std::vector<double>> mySecondMatrix) {
  int colsNum = mySecondMatrix[0].size();
  int rowsNumb = myFirstMatrix.size();
  std::vector<std::vector<double>> myResCRS = fillZero(colsNum, rowsNumb);
  for (int rr = 0; rr < rowsNumb; rr++) {
    for (int cc = 0; cc < colsNum; cc++) {
      myResCRS[rr][cc] = 0;
      for (size_t k = 0; k < myFirstMatrix[0].size(); k++) {
        myResCRS[rr][cc] += myFirstMatrix[rr][k] * mySecondMatrix[k][cc];
      }
    }
  }
  return myResCRS;
}

TEST(MatrixCRS_support, make_and_fill_zero_matrix) {
  EXPECT_NO_THROW(fillZero(5, 5));
}
TEST(MatrixCRS_support, random_vector_matrix) {
  EXPECT_NO_THROW(createRandomMatrix(5, 5, 0.5));
}
TEST(MatrixCRS_support, vector_matrix_big_density) {
  EXPECT_ANY_THROW(createRandomMatrix(5, 5, 2));
}
TEST(MatrixCRS_support, vector_matrix_oppos_density) {
  EXPECT_ANY_THROW(createRandomMatrix(5, 5, -2));
}
TEST(MatrixCRS, matrix_mult_vec) {
  std::vector<std::vector<double>> ve1 = {{0, 8}, {0, 2}};
  std::vector<std::vector<double>> ve2 = {{1, 0}, {1, 0}};
  std::vector<std::vector<double>> ve3 = {{8, 0}, {2, 0}};
  EXPECT_EQ(multiplyVecMatrix(ve1, ve2), ve3);
}

TEST(CRSMatrix, create_crs_matrix) {
  std::vector<std::vector<double>> veMatrix = {
      {0, 5},
      {9, 0},
      {0, 6},
  };
  EXPECT_NO_THROW(CRSMatrix resCRS(veMatrix));
}

TEST(CRSMatrix, can_transp_CRSMatrix) {
  std::vector<double> row1 = {0, 0, 0, 8};
  std::vector<double> row2 = {6, 0, 0, 0};
  std::vector<double> row3 = {0, 15, 0, 0};
  std::vector<double> row4 = {6, 0, 0, 0};
  std::vector<double> row5 = {0, 1, 0, 72};
  std::vector<std::vector<double>> vT = {row1, row2, row3, row4, row5};

  std::vector<double> res1 = {0, 6, 0, 6, 0};
  std::vector<double> res2 = {0, 0, 15, 0, 1};
  std::vector<double> res3 = {0, 0, 0, 0, 0};
  std::vector<double> res4 = {8, 0, 0, 0, 72};
  std::vector<std::vector<double>> resMatrix = {res1, res2, res3, res4};
  EXPECT_EQ(CRSMatrix(vT).MatrixTransp(), CRSMatrix(resMatrix));
}
TEST(CRSMatrix, random_mult_CRSMatrix) {
  std::vector<std::vector<double>> veM1 = createRandomMatrix(3, 3, 0.4);
  std::vector<std::vector<double>> veM2 = createRandomMatrix(3, 3, 0.4);
  CRSMatrix myCRSMatr1(veM1);
  CRSMatrix myCRSMatr2(veM2);
  EXPECT_EQ(myCRSMatr1.MatrixMult(myCRSMatr2.MatrixTransp()),
            CRSMatrix(multiplyVecMatrix(veM1, veM2)));
}
TEST(CRSMatrix, expected_mult_CRSMatrix) {
  CRSMatrix firstM(6, 6, {1, 2, 3, 4, 2, 5, 7}, {0, 4, 2, 3, 3, 5, 1},
                   {0, 2, 4, 4, 6, 6, 7});
  CRSMatrix secondM(6, 6, {3, 1, 1, 3, 1, 3, 2, 4}, {0, 5, 2, 3, 0, 2, 1, 4},
                    {0, 2, 3, 3, 4, 6, 8});
  CRSMatrix resM(6, 6, {5, 6, 1, 12, 10, 6, 20, 7}, {0, 2, 5, 3, 1, 3, 4, 2},
                 {0, 3, 4, 4, 7, 7, 8});
  CRSMatrix res = firstM.MatrixMult(secondM.MatrixTransp());
  EXPECT_EQ(res, resM);
}
TEST(CRSMatrix, mult_CRSMatrix_bad_size) {
  std::vector<std::vector<double>> veM1 = createRandomMatrix(3, 2, 0.4);
  std::vector<std::vector<double>> veM2 = createRandomMatrix(5, 4, 0.4);
  CRSMatrix myCRSMatr1(veM1);
  CRSMatrix myCRSMatr2(veM2);
  EXPECT_ANY_THROW(myCRSMatr1.MatrixMult(myCRSMatr2.MatrixTransp()));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
