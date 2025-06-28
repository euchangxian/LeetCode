#include <algorithm>
#include <functional>
#include <utility>
#include <vector>

class Solution {
 public:
  std::vector<int> maxSubsequence(std::vector<int>& nums, int k) {
    // Find a subsequence of length k with the largest sum.
    // Top K?
    // We need to return the subsequence, therefore can't sort/nth-element
    // Simplest is extra O(N) space with index. Then sort.
    // Otherwise, PQ of top k, storing index.
    auto n = static_cast<int>(nums.size());

    std::vector<std::pair<int, int>> withIndex;
    withIndex.reserve(n);
    for (int i = 0; i < n; ++i) {
      withIndex.emplace_back(nums[i], i);
    }

    std::nth_element(withIndex.begin(), withIndex.begin() + k, withIndex.end(),
                     std::greater<>{});
    std::ranges::sort(
        withIndex.begin(), withIndex.begin() + k, {},
        &std::pair<int, int>::second);  // sort by ascending index.
    std::vector<int> result;
    for (int i = 0; i < k; ++i) {
      result.push_back(withIndex[i].first);
    }

    return result;
  }
};
