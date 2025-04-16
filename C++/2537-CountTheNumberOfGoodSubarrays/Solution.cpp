#include <unordered_map>
#include <vector>

using i64 = long long;

class Solution {
 public:
  i64 countGood(std::vector<int>& nums, int k) {
    // A subarray is good if there are at least k pairs of indices (i, j) such
    // that i < j and arr[i] == arr[j].
    // Return the number of good subarrays.
    // First thought is sliding window. Shrink when there are at least k pairs,
    // expand otherwise.
    // If there are at least k pairs in the subarray arr[l..r], then there are
    // at least k pairs in the subarray arr[i..r] for 0 <= i <= l.
    // Thus, the total number of good subarrays ending at arr[r] can be counted
    // with l.
    const int n = nums.size();

    i64 result = 0;

    // window frequency.
    std::unordered_map<int, int> freq;
    freq.reserve(n);
    int l = 0;
    for (int r = 0; r < n; ++r) {
      k -= freq[nums[r]]++;
      while (k <= 0) {
        k += --freq[nums[l++]];
      }
      result += l;
    }
    return result;
  }
};
