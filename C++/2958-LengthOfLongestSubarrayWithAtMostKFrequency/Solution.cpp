#include <algorithm>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  int maxSubarrayLength(std::vector<int>& nums, int k) {
    // Frequency of x is the number of times it occurs in nums.
    // An subarray is good if the frequency of each element is <=k
    // Return the longest good subarray.
    //
    // Sounds like sliding window at first glance.
    // If frequency(x) > k, we can shrink until frequency(x) <= k.
    // We never need discarded elements.
    const auto n = static_cast<int>(nums.size());
    std::unordered_map<int, int> freq;
    freq.reserve(n);

    auto result = 0;
    auto curr = 0;
    for (auto l = 0, r = 0; r < n; ++r) {
      ++freq[nums[r]];
      ++curr;
      while (freq[nums[r]] > k) {
        --freq[nums[l++]];
        --curr;
      }

      result = std::max(result, curr);
    }
    return result;
  }
};
