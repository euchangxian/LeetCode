#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  std::vector<int> sortByBits(std::vector<int>& arr) {
    std::sort(arr.begin(), arr.end(), [](int a, int b) {
      // For a comparator comp(a, b), it must define a strict weak ordering.
      // That is, it must satisfy these properties:
      // 1. Irreflexivity: comp(x, x) == false
      // 2. Asymmetry: if comp(x, y) == true, then comp(y, x) == false, and vice
      //               versa.
      // 3. Transitivity: If comp(x, y) == true && comp(y, z) == true then
      //                  comp(x, z) = true.
      return __builtin_popcount(a) < __builtin_popcount(b) ||
             (__builtin_popcount(a) == __builtin_popcount(b) && a < b);
    });
    return arr;
  }
};
