#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
 public:
  int maxDistance(vector<vector<int>>& arrays) {
    // At the i-th array, the prevMin and prevMax should represent the maximum
    // and minimum elements up to the (i-1)th array. This ensures that we never
    // take the distance between elements in the same array.
    int prevMin = arrays[0][0];
    int prevMax = arrays[0][arrays[0].size() - 1];
    int result = INT_MIN;

    for (int i = 1; i < arrays.size(); ++i) {
      vector<int> const& current = arrays[i];
      int m = current.size();
      // Check the difference between the current max and prevMin, and
      // the current min and prevMax;
      result = max(result, max(current[m - 1] - prevMin, prevMax - current[0]));

      prevMin = min(prevMin, current[0]);
      prevMax = max(prevMax, current[m - 1]);
    }

    return result;
  }
};
