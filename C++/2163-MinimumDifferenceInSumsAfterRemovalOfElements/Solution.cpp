#include <algorithm>
#include <limits>
#include <queue>
#include <vector>

using i64 = long long;
class Solution {
 public:
  i64 minimumDifference(std::vector<int>& nums) {
    // Given 0-indexed nums consisting of 3*n elements.
    // Remove a subsequence of elements of size exactly n, and partition the
    // remaining 2*n elements into two equal parts of size n each.
    // - First n elements have sum_first
    // - Second n elements have sum_second
    // Minimise the difference = sum_first - sum_second
    //
    // Hm. Partitioning question. We want to maximise sum_second, and minimise
    // sum_first.
    // Feels like removing a non-increasing subsequence of size n.
    // From another perspective, we want to minimise the prefix sum at index i.
    const auto n = static_cast<int>(nums.size()) / 3;

    std::priority_queue<int> smallestN;

    std::vector<i64> prefix(nums.size());
    i64 prefixSum = 0;
    for (int i = 0; i < nums.size() - n; ++i) {
      smallestN.emplace(nums[i]);
      prefixSum += nums[i];

      if (smallestN.size() > n) {
        prefixSum -= smallestN.top();
        smallestN.pop();
      }
      if (smallestN.size() == n) {
        prefix[i] = prefixSum;
      }
    }

    i64 result = std::numeric_limits<i64>::max();

    // NOTE: negate integers to push into largestN.
    std::priority_queue<int> largestN;
    i64 suffixSum = 0;
    for (int i = nums.size() - 1; i >= n; --i) {
      largestN.emplace(-nums[i]);
      suffixSum += nums[i];
      if (largestN.size() > n) {
        suffixSum += largestN.top();  // negate
        largestN.pop();
      }

      if (largestN.size() == n) {
        result = std::min(result, prefix[i - 1] - suffixSum);
      }
    }
    return result;
  }
};
