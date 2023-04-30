// Copyright 2023 Kandrin Alexey
#ifndef MODULES_TASK_2_KANDRIN_A_COMPONENT_MARKING_COMPONENT_MARKING_H_
#define MODULES_TASK_2_KANDRIN_A_COMPONENT_MARKING_COMPONENT_MARKING_H_

#pragma region HelperClasses

#include <ostream>
#include <random>
#include <vector>

//=============================================================================
// Class   : Matrix
// Purpose : Storing a two-dimensional matrix as a one-dimensional array.
//=============================================================================
template <class T>
class Matrix {
  size_t m_rowCount{0};
  size_t m_colCount{0};
  std::vector<T> m_matrixData{};

 public:
  Matrix() = default;
  Matrix(const Matrix& matrix) = default;
  Matrix(Matrix&& matrix) = default;
  Matrix& operator=(const Matrix&) = default;
  Matrix& operator=(Matrix&&) = default;

  Matrix(size_t rowCount, size_t colCount, const T& value = T())
      : m_rowCount(rowCount),
        m_colCount(colCount),
        m_matrixData(rowCount * colCount, value) {}

  typename std::vector<T>::iterator begin() { return m_matrixData.begin(); }

  typename std::vector<T>::const_iterator begin() const {
    return m_matrixData.begin();
  }

  typename std::vector<T>::iterator end() { return m_matrixData.end(); }

  typename std::vector<T>::const_iterator end() const {
    return m_matrixData.end();
  }

  T* data() { return m_matrixData.data(); }

  const T* data() const { return m_matrixData.data(); }

  T* operator[](size_t index) {
    T* rowPtr = m_matrixData.data() + index * m_colCount;
    return rowPtr;
  }

  const T* operator[](size_t index) const {
    const T* rowPtr = m_matrixData.data() + index * m_colCount;
    return rowPtr;
  }

  bool operator==(const Matrix& other) const {
    return m_rowCount == other.m_rowCount && m_colCount == other.m_colCount &&
           m_matrixData == other.m_matrixData;
  }

  bool empty() const { return m_matrixData.empty(); }

  void clear() { m_matrixData.clear(); }

  size_t GetRowCount() const { return m_rowCount; }

  size_t GetColCount() const { return m_colCount; }

  friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    for (size_t i = 0; i < matrix.m_rowCount; ++i) {
      for (size_t j = 0; j < matrix.m_colCount; ++j) {
        os << matrix[i][j] << ' ';
      }
      os << '\n';
    }
    return os;
  }
};

//=============================================================================
// Class   : WorkSplitter
// Purpose : Calculating how much work the worker needs to do.
//=============================================================================
class WorkSplitter {
  std::vector<size_t> m_workDistribution;

 public:
  // Constructor.
  // \param work Total amount of work.
  // \param workerCount Total number of workers who can do the work.
  WorkSplitter(size_t work, size_t workerCount);

  // Determining how much work a worker should do.
  // \param workerNumber The worker for whom we calculate how much work he has
  // to do. \return What part of the work should worker do. (If there are fewer
  // work than workerCount, then some workers will do nothing. If work is
  // proportional to the workerCount, then all workers will do the same amount
  // of work)
  size_t GetPartWork(size_t workerNumber) const;
};

//=============================================================================
// Function : GetRandomMatrix
// Purpose  : Generating a matrix of given sizes and filling it with random
//            values.
//=============================================================================
template <class T, class RandomFunctor>
Matrix<T> GetRandomMatrix(size_t rowCount, size_t colCount,
                          RandomFunctor&& random) {
  Matrix<T> matrix(rowCount, colCount);
  for (size_t i = 0; i < rowCount; ++i) {
    for (size_t j = 0; j < colCount; ++j) {
      matrix[i][j] = random();
    }
  }
  return matrix;
}

#pragma endregion HelperClasses

// Binary pixel (using bool failed due to the existence
// specialization vector<bool>)
using BinaryPixel = char;
using BinaryImage = Matrix<BinaryPixel>;  // binary image

using Label = unsigned int;        // type for label
using LabelImage = Matrix<Label>;  // labeled image

// Execution Policy
enum class ExecutionPolicy {
  Sequential,  // sequential execution
  Parallel     // parallel execution
};

// Implementation of getting labeling of connectivity components
template <ExecutionPolicy executionPolicy>
LabelImage GetComponentMarkingImp(const BinaryImage& source);

// Implementation of getting labeling of connectivity components (sequential
// implementation)
template <>
LabelImage GetComponentMarkingImp<ExecutionPolicy::Sequential>(
    const BinaryImage& source);

// Implementation of getting labeling of connectivity components (parallel
// implementation)
template <>
LabelImage GetComponentMarkingImp<ExecutionPolicy::Parallel>(
    const BinaryImage& source);

// Get labeled connectivity components
template <ExecutionPolicy executionPolicy>
LabelImage GetComponentMarking(const BinaryImage& sourceImage) {
  return GetComponentMarkingImp<executionPolicy>(sourceImage);
}

#endif  // MODULES_TASK_2_KANDRIN_A_COMPONENT_MARKING_COMPONENT_MARKING_H_
