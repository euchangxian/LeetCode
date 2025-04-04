#include <cstddef>
#include <queue>
#include <utility>
#include <vector>

/**
 * A queue can be used
 */
class ZigzagIterator {
 private:
  // {iter, end}
  std::queue<std::pair<std::vector<int>::iterator, std::vector<int>::iterator>>
      iters;

 public:
  ZigzagIterator(std::vector<int>& v1, std::vector<int>& v2) {
    // Only need one check. Since a call to next() will be valid.
    if (!v1.empty()) {
      iters.emplace(v1.begin(), v1.end());
    }
    if (!v2.empty()) {
      iters.emplace(v2.begin(), v2.end());
    }
  }

  int next() {
    auto [iterBegin, iterEnd] = iters.front();
    iters.pop();

    // Guaranteed valid
    const int val = *iterBegin;
    iterBegin = std::next(iterBegin);

    if (iterBegin != iterEnd) {
      iters.emplace(iterBegin, iterEnd);
    }
    return val;
  }

  bool hasNext() { return !iters.empty(); }
};

/**
 * Your ZigzagIterator object will be instantiated and called as such:
 * ZigzagIterator i(v1, v2);
 * while (i.hasNext()) cout << i.next();
 */
