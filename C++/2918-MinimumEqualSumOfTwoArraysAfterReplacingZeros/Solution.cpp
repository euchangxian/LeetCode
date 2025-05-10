#include <algorithm>
#include <string_view>
#include <utility>
#include <vector>

using i64 = long long;
class Solution {
 public:
  i64 minSum(std::vector<int>& nums1, std::vector<int>& nums2) {
    i64 sum1 = 0LL, sum2 = 0LL;
    int zeroes1 = 0, zeroes2 = 0;

    for (int x : nums1) {
      sum1 += x;
      zeroes1 += (x == 0);
    }
    for (int x : nums2) {
      sum2 += x;
      zeroes2 += (x == 0);
    }

    sum1 += zeroes1;
    sum2 += zeroes2;

    if ((sum2 > sum1 && zeroes1 == 0) || (sum1 > sum2 && zeroes2 == 0)) {
      return -1LL;
    }
    return std::max(sum1, sum2);
  }

  i64 minSumEnumeration(std::vector<int>& nums1, std::vector<int>& nums2) {
    // two arrays nums1 and nums2 of positive integers.
    // Replace all 0s in both arrays such that the sum of both elements become
    // equal.
    // Minimum equal sum, or -1 if impossible.
    //
    // Greedy set 0s to as small as possible.
    // WLOG, let sum1 <= sum2.
    // diff=sum2-sum1
    // zDiff=zeroes2-zeroes1
    // if diff > 0:
    //   - if zeroes1 == 0, not possible
    //   - if zeroes2 == 0, and sum1+zeroes1 > sum2, not possible
    //   - if diff+zeroes2 >= zeroes1, return sum2+zeroes2, set all zeroes2 to 1
    //   - otherwise, return sum2+zeroes1
    // if diff == 0:
    //   - if exactly one of zeroes1 or zeroes2 is non-zero, not possible.
    //   - otherwise, return sum2+max(zeroes1,zeroes2)
    i64 sum1 = 0LL, sum2 = 0LL;
    int zeroes1 = 0, zeroes2 = 0;

    for (int x : nums1) {
      sum1 += x;
      zeroes1 += (x == 0);
    }
    for (int x : nums2) {
      sum2 += x;
      zeroes2 += (x == 0);
    }

    if (sum1 > sum2) {
      std::swap(sum1, sum2);
      std::swap(zeroes1, zeroes2);
    }

    i64 diff = sum2 - sum1;
    if (diff == 0) {
      if ((zeroes1 == 0) ^ (zeroes2 == 0)) {
        return -1LL;
      }
      return sum2 + std::max(zeroes1, zeroes2);
    }

    if (zeroes1 == 0) {
      return -1LL;
    }
    if (zeroes2 == 0 && sum1 + zeroes1 > sum2) {
      return -1LL;
    }

    if (diff + zeroes2 < zeroes1) {
      return sum1 + zeroes1;
    }
    return sum2 + zeroes2;
  }
};
