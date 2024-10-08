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
  int rangeSum(vector<int>& nums, int n, int left, int right) {
    vector<int> subarraySums;
    subarraySums.reserve(n * (n + 1) / 2);

    for (int i = 0; i < n; ++i) {
      int sum = 0;
      // for every index ahead of the current index
      for (int j = i; j < n; ++j) {
        sum += nums[j];
        subarraySums.push_back(sum);
      }
    }

    sort(subarraySums.begin(), subarraySums.end());

    int rangeSum = 0;
    const int MOD = 1e9 + 7;

    for (int i = left - 1; i < right; ++i) {
      rangeSum = (rangeSum + subarraySums[i]) % MOD;
    }
    return rangeSum;
  }
};
