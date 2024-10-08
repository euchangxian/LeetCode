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
  int maxScoreSightseeingPair(vector<int>& values) {
    int n = values.size();

    // Maintain the maximum score pair so-far
    int result = 0;

    // Maintain the maximum value to the left, normalized by
    // the distance from the current index i
    int prefixMax = values[0];

    for (int i = 1; i < n; ++i) {
      result = max(result, prefixMax - 1 + values[i]);

      // Update prefixMax by checking if taking a previous value
      // is worth the distance penalty, or simply take the current value
      prefixMax = max(prefixMax - 1, values[i]);
    }
    return result;
  }
};
