#include <algorithm>
#include <utility>
#include <vector>

class Solution {
 public:
  bool hasIncreasingSubarrays(std::vector<int>& nums, int k) {
    // determine if there exists two adjacent subarrays of length k, such that
    // both subarrays are strictly increasing.
    //
    // Basically, if there is an increasing subarray starting at index a,
    // of length k, then check if theres an increasing subarray at index b,
    // where b=a+k.
    //
    // Stack? Not necessary. We are looking for subarrays, not subsequences.
    const auto n = static_cast<int>(nums.size());
    int curr = 1;
    int prev = 0;
    int result = 0;
    for (int i = 1; i < n; ++i) {
      if (nums[i] > nums[i - 1]) {
        ++curr;
      } else {
        prev = std::exchange(curr, 1);
      }
      result = std::max({result, curr / 2, std::min(prev, curr)});
    }
    return result >= k;
  }
};
