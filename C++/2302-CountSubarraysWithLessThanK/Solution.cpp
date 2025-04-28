#include <vector>

using i64 = long long;

class Solution {
 public:
  i64 countSubarrays(std::vector<int>& nums, i64 k) {
    // The score of a subarray is the product of its sum and length.
    // Given positive integer nums and integer k, return the number of non-empty
    // subarrays of nums whose score is strictly less than k.
    //
    // Sliding Window? Shrink if sum * (r-l+1) < k.
    // Hm, we cant guarantee that the prefix nums[..l] is guaranteed to be
    // under k (usually counting by += l).
    // What if we count greater than equal to k?
    // 2 1 4 invalid,
    //   1 4
    //     4 count += l=2
    //     4 3 invalid,
    //       3 count += l=3
    //       3 5 invalid
    //         count += l=4
    // count = 9
    // total subarray = 5+4+3+2+1=15
    // result = total - count = 6
    //
    // 1 1 1 invalid
    //   1 1 count += l=1
    // result = 6-1 = 5
    const i64 n = nums.size();

    i64 result = n * (n + 1LL) / 2LL;
    i64 sum = 0LL;
    for (i64 l = 0LL, r = 0LL; r < n; ++r) {
      sum += nums[r];
      while (sum * (r - l + 1LL) >= k) {
        sum -= nums[l++];
      }
      result -= l;
    }
    return result;
  }
};
