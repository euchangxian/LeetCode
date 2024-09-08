#include <algorithm>
#include <array>
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
  int lengthOfLIS(vector<int> &nums) {
    int n = nums.size();

    // Let dp[i] represent the longest increasing subsequence at i
    vector<int> dp(n, 1);
    for (int i = 1; i < n; ++i) {
      for (int j = 0; j < i; ++j) {
        if (nums[i] > nums[j]) {
          dp[i] = max(dp[i], dp[j] + 1);
        }
      }
    }

    return *max_element(dp.begin(), dp.end());
  }
};
