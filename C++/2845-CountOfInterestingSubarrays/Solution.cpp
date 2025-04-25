#include <unordered_map>
#include <vector>

using i64 = long long;
class Solution {
 public:
  i64 countInterestingSubarrays(std::vector<int>& nums, int modulo, int k) {
    // Count interesting subarrays.
    // A subarray nums[l..r] is interesting if:
    // - COUNT is the number of indices i such that nums[i] % modulo == k,
    //   for all l <= i <= r,
    // - and COUNT % modulo == k
    //
    // Sliding window? we only count valid if count%modulo == k?
    // There is seemingly an edge case where k == 0? Then we want to consider
    // subarrays that have COUNT=0.
    //
    // Hm. Feels more like prefixes? prefixCOUNT key-ed by the remainder?
    // That way, if modulo=5, k=1, prefix[i] = 8, we need (8-2)%5 == 1, or
    //                                                    (8-7)%5 == 1
    // i.e., index where prefix=2, and prefix=7
    // the target counts is obtainable from prefix - c*k, where c >= 0
    // Hm. We can store prefix%count given properties of modulo arithmetic
    const int n = nums.size();
    i64 result = 0;

    std::unordered_map<int, int> freq;
    freq[0] = 1;
    int prefix = 0;
    for (int i = 0; i < n; ++i) {
      prefix += (nums[i] % modulo) == k;
      int target = (prefix - k + modulo) % modulo;  // possibly negative, +mod.

      result += freq[target];
      ++freq[prefix % modulo];
    }
    return result;
  }
};
