#include <vector>

class Solution {
 public:
  bool isZeroArray(std::vector<int>& nums,
                   std::vector<std::vector<int>>& queries) {
    // queries[i] = [l, r]
    // For each query:
    // - select a subset of indices within [l, r] in nums
    // - decrement all selected indices by 1
    // Return true if it is possible to make nums zero.
    //
    // Range Update Data Structures make this trivial.
    // Line Sweep works too given we have offline queries.
    const int n = nums.size();
    std::vector<int> events(n + 1, 0);
    for (const auto& query : queries) {
      ++events[query[0]];
      --events[query[1] + 1];  // exclusive
    }

    int pref = 0;
    for (int i = 0; i < n; ++i) {
      pref += events[i];
      if (nums[i] > pref) {
        return false;
      }
    }
    return true;
  }
};
