#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <vector>

class Vector2D {
 private:
  const std::vector<std::vector<int>>::iterator rowEnd;

  std::vector<std::vector<int>>::iterator rowIter;
  std::vector<int>::iterator colIter;

 public:
  // Initialize a copy. Not sure if std::move makes sense semantically here.
  Vector2D(std::vector<std::vector<int>>& vec)
      : rowIter(vec.begin()), rowEnd(vec.end()) {
    if (rowIter != rowEnd) {
      colIter = rowIter->begin();
    }
  }

  int next() {
    if (!hasNext()) {
      throw std::out_of_range("wont reach here");
    }

    // Call to next() is valid.
    const int val = *colIter;
    colIter = std::next(colIter);
    return val;
  }

  // Besides checking for bounds, also move the iterators.
  bool hasNext() {
    while (rowIter != rowEnd && colIter == rowIter->end()) {
      rowIter = std::next(rowIter);

      if (rowIter != rowEnd) {
        colIter = rowIter->begin();
      }
    }

    return rowIter != rowEnd;
  }
};

/**
 * Your Vector2D object will be instantiated and called as such:
 * Vector2D* obj = new Vector2D(vec);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
