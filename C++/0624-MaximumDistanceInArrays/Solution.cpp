#include <algorithm>
#include <climits>
#include <vector>

class Solution {
 public:
  int maxDistance(std::vector<std::vector<int>>& arrays) {
    // At the i-th array, the prevMin and prevMax should represent the maximum
    // and minimum elements up to the (i-1)th array. This ensures that we never
    // take the distance between elements in the same array.
    int prevMin = arrays[0][0];
    int prevMax = arrays[0][arrays[0].size() - 1];
    int result = INT_MIN;

    for (int i = 1; i < arrays.size(); ++i) {
      const std::vector<int>& current = arrays[i];
      int m = current.size();
      // Check the difference between the current max and prevMin, and
      // the current min and prevMax;
      result = std::max(
          result, std::max(current[m - 1] - prevMin, prevMax - current[0]));

      prevMin = std::min(prevMin, current[0]);
      prevMax = std::max(prevMax, current[m - 1]);
    }

    return result;
  }
};
