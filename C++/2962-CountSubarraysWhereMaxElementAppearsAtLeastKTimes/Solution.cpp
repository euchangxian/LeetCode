#include <algorithm>
#include <vector>

using i64 = long long;
class Solution {
 public:
  i64 countSubarrays(std::vector<int>& nums, int k) {
    // Return number of subarrays where the max of NUMS appear at least
    // k times.
    // Straightforward sliding window shrink when >=k
    const int n = nums.size();
    const int max = *std::ranges::max_element(nums);

    int freq = 0;
    i64 result = 0;
    for (i64 l = 0LL, r = 0LL; r < n; ++r) {
      freq += nums[r] == max;
      while (freq >= k) {
        freq -= nums[l++] == max;
      }
      result += l;
    }
    return result;
  }
};
