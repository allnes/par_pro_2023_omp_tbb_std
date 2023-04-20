// Copyright 2023 Kandrin Alexey
#include "../../../modules/task_4/kandrin_a_component_marking/component_marking.h"

#include <algorithm>
#include <cassert>

#pragma region HelperClassesImplementation

//=============================================================================
// Function : WorkSplitter::WorkSplitter
// Purpose  : Constructor.
//=============================================================================
WorkSplitter::WorkSplitter(size_t work, size_t workerCount)
    : m_workDistribution(workerCount, 0) {
  if (work <= workerCount) {
    for (size_t currentWorker = 0; currentWorker < work; ++currentWorker) {
      m_workDistribution[currentWorker] = 1;
    }
  } else {
    for (size_t currentWorker = 0; work != 0; ++currentWorker) {
      size_t workForCurrentWorker = work / workerCount;
      m_workDistribution[currentWorker] = work / workerCount;
      work -= workForCurrentWorker;
      workerCount -= 1;
    }
  }
}

//=============================================================================
// Function : GetPartWork
// Purpose  : Determining how much work a worker should do.
//=============================================================================
size_t WorkSplitter::GetPartWork(size_t workerNumber) const {
  return m_workDistribution[workerNumber];
}

//=============================================================================
// Function : GetPartWork
// Purpose  : Determining how much work a worker should do.
//=============================================================================
size_t WorkSplitter::GetWorker(size_t partWorkBegin, size_t partWorkEnd) {
  size_t currentWorkerWorkBegin = 0;
  for (size_t i = 0; i < m_workDistribution.size(); ++i) {
    size_t currentWorkerWorkEnd =
        currentWorkerWorkBegin + m_workDistribution[i];
    if (partWorkBegin >= currentWorkerWorkBegin &&
        partWorkEnd <= currentWorkerWorkEnd) {
      assert(partWorkBegin == currentWorkerWorkBegin &&
             partWorkEnd == currentWorkerWorkEnd);
      return i;
    }

    currentWorkerWorkBegin = currentWorkerWorkEnd;
  }
  assert(false);
  return -1;
}

#pragma endregion HelperClassesImplementation

namespace {
// maximum allowable number of connectivity components in an image
constexpr size_t maxLabelCount = 10000;

// Parent - an array for storing labels, having a tree structure.
// In this array, the element index should be interpreted as the value of the
// label, And the value at this index is the value of the parent label. That is,
// parent[label_1] == parent_label_of_label_1. If the label has no parent label,
// then instead of the value of the parent label 0 is written.
using Parent = std::vector<Label>;

// Find parent label for given label
Label FindParent(Label label, const Parent& parent) {
  while (parent[label] != 0) {
    label = parent[label];
  }
  return label;
}

// Union of two sets
template <ExecutionPolicy executionPolicy>
void Union(Label x, Label y, Parent* parent);

// Union of two sets (sequential implementation)
template <>
void Union<ExecutionPolicy::Sequential>(Label x, Label y, Parent* parent) {
  x = FindParent(x, *parent);
  y = FindParent(y, *parent);
  if (x != y) {
    parent->at(y) = x;
  }
}

// Union of two sets (parallel implementation)
template <>
void Union<ExecutionPolicy::Parallel>(Label x, Label y, Parent* parent) {
  parallel_invoke([&x, parent]() { x = FindParent(x, *parent); },
                  [&y, parent]() { y = FindParent(y, *parent); });

  if (x != y) {
    parent->at(y) = x;
  }
}

// Position of element (row/column)
struct Position {
  size_t x;  // row
  size_t y;  // column
  Position(size_t x, size_t y) : x(x), y(y) {}
};

// Get positions of prior neighbors
std::vector<Position> GetPriorNeighbors(const BinaryImage& image, size_t i,
                                        size_t j) {
  // obtaining 2 neighbors (northern and western with 4-connectivity)
  std::vector<Position> result;
  if (image.empty()) return result;

  // upper neighbor
  if (i > 0) {
    result.emplace_back(i - 1, j);
  }

  // left neighbor
  if (j > 0) {
    result.emplace_back(i, j - 1);
  }

  return result;
}

// Get (already assigned) labels
std::vector<BinaryPixel> GetLabels(
    const LabelImage& image, const std::vector<Position>& priorNeighbors) {
  std::vector<BinaryPixel> result;
  for (auto&& position : priorNeighbors) {
    size_t i = position.x;
    size_t j = position.y;
    if (image[i][j] != 0) result.push_back(image[i][j]);
  }
  return result;
}

// The method corrects the values of the elements in the arr array in such a way
// that so that the set of values of the array elements does not have "gaps".
// For example, if the set of array element values is {1, 3, 7, 10},
// Then it will turn into {1, 2, 3, 4}
// Accordingly, the arr array equal to {1, 3, 10, 7, 1, 3, 10, 7, 1} will become
// in {1, 2, 4, 3, 1, 2, 4, 3, 1}
template <ExecutionPolicy>
void FixNumeration(Label* arr, size_t size);

// Fix numeration (sequential implementation)
template <>
void FixNumeration<ExecutionPolicy::Sequential>(Label* arr, size_t size) {
  static_assert(
      std::is_unsigned<std::remove_reference_t<decltype(*arr)>>::value,
      "This algorithm assumes that the label is unsigned");

  assert(arr != nullptr);
  if (arr == nullptr) return;

  std::vector<bool> isLabelExist(maxLabelCount, false);
  for (size_t i = 0; i < size; ++i) {
    assert(arr[i] <
           isLabelExist.size());  // it is assumed that in the arr array now
                                  // possible from 0 to maxLabelCount
    isLabelExist[arr[i]] = true;
  }

  // Get the value of the maximum label (to optimize the next loop)
  Label maxLabel = 0;
  for (size_t i = 0; i < size; ++i) {
    if (arr[i] > maxLabel) {
      maxLabel = arr[i];
    }
  }

  // Get a list of replacements

  // Structure to replace
  struct Replace {
    Label before;  // previous label value (to be changed)
    Label after;   // new label value (to be changed to)

    Replace(BinaryPixel before, BinaryPixel after)
        : before(before), after(after) {}
  };
  std::vector<Replace> replaceArr;  // list of replacements

  Label currentNumber = 1;  // variable for numeration
  for (Label currentLabel = 1; currentLabel <= maxLabel;) {
    // currentLabel - the value of the current label
    // if no such label exists, then go to the nearest existing label
    // In this loop, we cannot go beyond the allowed range [1; maxLabel] because
    // the label maxLabel must exist.
    while (!isLabelExist[currentLabel]) ++currentLabel;

    if (currentLabel != currentNumber) {
      // if the current label is not equal to the current number, then add
      // "replacement" to list of replacements
      replaceArr.emplace_back(currentLabel, currentNumber);
    }

    ++currentLabel;
    ++currentNumber;
  }

  for (auto&& replace : replaceArr) {
    for (size_t i = 0; i < size; ++i) {
      if (arr[i] == replace.before) arr[i] = replace.after;
    }
  }
}

// Fix numeration (parallel implementation)
template <>
void FixNumeration<ExecutionPolicy::Parallel>(Label* arr, size_t size) {
  static_assert(
      std::is_unsigned<std::remove_reference_t<decltype(*arr)>>::value,
      "This algorithm assumes that the label is unsigned");

  assert(arr != nullptr);
  if (arr == nullptr) return;

  std::vector<char> isLabelExist(
      maxLabelCount, false);  // "bool" can not be used here
                              // due to to the presence of an inappropriate (in
                              // this case) specialization std::vector<bool>
  parallel_for(
      size, [&isLabelExist, arr](const size_t begin, const size_t end) {
        for (auto index = begin; index != end; ++index) {
          assert(arr[index] <
                 isLabelExist.size());  // it is assumed that in the arr array
                                        // now possible from 0 to maxLabelCount
          isLabelExist[arr[index]] = true;
        }
      });

  // Get the value of the maximum label (to optimize the next loop)
  Label maxLabel = parallel_reduce(
      size, Label{0},
      [arr](const size_t begin, const size_t end, Label maxLabel) {
        for (auto index = begin; index != end; ++index) {
          if (arr[index] > maxLabel) {
            maxLabel = arr[index];
          }
        }
        return maxLabel;
      },
      static_cast<const Label& (*)(const Label&, const Label&)>(
          &std::max<Label>));

  // Get a list of replacements

  // Structure to replace
  struct Replace {
    Label before;  // previous label value (to be changed)
    Label after;   // new label value (to be changed to)

    Replace(BinaryPixel before, BinaryPixel after)
        : before(before), after(after) {}
  };
  std::vector<Replace> replaceArr;  // list of replacements

  Label currentNumber = 1;  // variable for numeration
  for (Label currentLabel = 1; currentLabel <= maxLabel;) {
    // currentLabel - the value of the current label
    // if no such label exists, then go to the nearest existing label
    // In this loop, we cannot go beyond the allowed range [1; maxLabel] because
    // the label maxLabel must exist.
    while (!isLabelExist[currentLabel]) ++currentLabel;

    if (currentLabel != currentNumber) {
      // if the current label is not equal to the current number, then add
      // "replacement" to list of replacements
      replaceArr.emplace_back(currentLabel, currentNumber);
    }

    ++currentLabel;
    ++currentNumber;
  }

  for (auto&& replace : replaceArr) {
    parallel_for(size, [arr, &replace](const size_t begin, const size_t end) {
      for (auto index = begin; index != end; ++index) {
        if (arr[index] == replace.before) arr[index] = replace.after;
      }
    });
  }
}
}  // namespace

// Get labeling of connectivity components (sequential implementation)
template <>
LabelImage GetComponentMarkingImp<ExecutionPolicy::Sequential>(
    const BinaryImage& source) {
  LabelImage result(source.GetRowCount(), source.GetColCount(), 0);

  Parent parent(maxLabelCount, 0);
  Label label = 1;

  Label m = 0;
  for (size_t i = 0; i < source.GetRowCount(); ++i) {
    for (size_t j = 0; j < source.GetColCount(); ++j) {
      if (source[i][j] == 1) {
        auto priorNeighbors = GetPriorNeighbors(source, i, j);
        auto labels = GetLabels(result, priorNeighbors);
        if (labels.empty()) {
          m = label;
          label++;
        } else {
          m = *std::min_element(labels.begin(), labels.end());
        }
        result[i][j] = m;
        for (auto label : labels) {
          if (label != m) {
            Union<ExecutionPolicy::Sequential>(m, label, &parent);
          }
        }
      }
    }
  }

  for (size_t i = 0; i < source.GetRowCount(); ++i) {
    for (size_t j = 0; j < source.GetColCount(); ++j) {
      if (source[i][j] == 1) {
        result[i][j] = FindParent(result[i][j], parent);
      }
    }
  }

  FixNumeration<ExecutionPolicy::Sequential>(
      result.data(), result.GetRowCount() * result.GetColCount());

  return result;
}

// Get labeling of connectivity components (parallel implementation)
template <>
LabelImage GetComponentMarkingImp<ExecutionPolicy::Parallel>(
    const BinaryImage& source) {
  LabelImage result(source.GetRowCount(), source.GetColCount(), 0);

  Parent parent(maxLabelCount, 0);
  Label label = 1;

  Label m = 0;
  for (size_t i = 0; i < source.GetRowCount(); ++i) {
    for (size_t j = 0; j < source.GetColCount(); ++j) {
      if (source[i][j] == 1) {
        auto priorNeighbors = GetPriorNeighbors(source, i, j);
        auto labels = GetLabels(result, priorNeighbors);
        if (labels.empty()) {
          m = label;
          label++;
        } else {
          m = *std::min_element(labels.begin(), labels.end());
        }
        result[i][j] = m;
        for (auto label : labels) {
          if (label != m) {
            Union<ExecutionPolicy::Parallel>(m, label, &parent);
          }
        }
      }
    }
  }

  auto plainArraySource = source.data();
  size_t plainArraySourceSize = source.GetRowCount() * source.GetColCount();
  auto plainArrayResult = result.data();

  parallel_for(plainArraySourceSize, [plainArraySource, plainArrayResult,
                                      &parent](const size_t begin,
                                               const size_t end) {
    for (auto index = begin; index != end; ++index) {
      if (plainArraySource[index] == 1) {
        plainArrayResult[index] = FindParent(plainArrayResult[index], parent);
      }
    }
  });

  FixNumeration<ExecutionPolicy::Parallel>(
      result.data(), result.GetRowCount() * result.GetColCount());

  return result;
}

// Get the maximum number of threads
size_t GetMaxThreads() { return std::thread::hardware_concurrency(); }
