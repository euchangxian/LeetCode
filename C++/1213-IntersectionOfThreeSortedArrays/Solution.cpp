#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  std::vector<int> arraysIntersection(std::vector<int>& arr1,
                                      std::vector<int>& arr2,
                                      std::vector<int>& arr3) {
    std::vector<int> intersections;
    intersections.reserve(
        std::max(arr1.size(), std::max(arr2.size(), arr3.size())));

    int p1 = 0;
    int p2 = 0;
    int p3 = 0;
    while (p1 < arr1.size() && p2 < arr2.size() && p3 < arr3.size()) {
      if (arr1[p1] == arr2[p2] && arr2[p2] == arr3[p3]) {
        intersections.push_back(arr1[p1]);
        ++p1;
        ++p2;
        ++p3;
        continue;
      }

      // Increase the lower-valued pointers
      int highest = std::max(arr1[p1], std::max(arr2[p2], arr3[p3]));

      if (arr1[p1] < highest) {
        ++p1;
      }

      if (arr2[p2] < highest) {
        ++p2;
      }

      if (arr3[p3] < highest) {
        ++p3;
      }
    }
    return intersections;
  }
};
