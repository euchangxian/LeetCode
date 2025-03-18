#include <vector>

class Solution {
 public:
  bool containsPattern(const std::vector<int>& arr, const int m, const int k) {
    // Fixed-size sliding window of size m, with a stride of m, starting
    // at every possible index, let this be the offset.
    // The pattern will be defined by the first window.
    // Note that the pattern must be consecutive

    if (m * k > arr.size()) {
      // No way to fit k patterns of size m
      return false;
    }

    // Initialized to m because the first window is a pattern itself, matching
    // m characters.
    int count = m;  // match count. NOT pattern count
    for (int i = m; i < arr.size(); ++i) {
      if (arr[i] != arr[i - m]) {
        // Patterns must be consecutive.
        count = m;
      }

      count += (arr[i] == arr[i - m]);

      if (count >= (k * m)) {
        // If there are k * m char matches, then there are k valid patterns of
        // size m
        return true;
      }
    }
    return false;
  }
};
