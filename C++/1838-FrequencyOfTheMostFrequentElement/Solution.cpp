#include <algorithm>
#include <vector>

using i64 = long long;
class Solution {
 public:
  int maxFrequency(std::vector<int>& nums, int k) {
    // In one operation, choose any nums[i] and increment it by 1.
    // Return the maximum possible frequency after at most K operations.
    //
    // Felt like BSTA on the target nums to increment nums[i] to,
    // but theres no monotonic property on the maximum frequency.
    //
    // Naively, we want to set each nums[i] as the target value.
    // Then, for each nums[j] < nums[i], apply operations in descending order
    // of nums[j] greedily.
    // O(N^2).
    //
    // Hm, from above, it feels like theres a window. Particularly, in a sorted
    // array, [l..r] represents the range where each element nums[l..r] can be
    // incremented to nums[r] in at most k operations, i.e., the sum of
    // differences is <= k.
    // We want the maximum length window. Extend right while ops <= k.
    // Shrink while ops > k
    // How to efficiently maintain ops? Not trivial lol.
    // Ah.. We can maintain sum(nums[l..r]). Then, the number of elements in
    // the range (r-l+1) * nums[r] - sum gives us the number of operations
    // required to increment all elements in the range to nums[r]
    const int n = nums.size();
    std::sort(nums.begin(), nums.end());
    int maxFreq = 1;
    i64 sum = 0;
    for (int l = 0, r = 0; r < n; ++r) {
      sum += nums[r];

      while (static_cast<i64>(r - l + 1) * nums[r] - sum > k) {
        sum -= nums[l++];
      }
      maxFreq = std::max(maxFreq, r - l + 1);
    }
    return maxFreq;
  }
};
