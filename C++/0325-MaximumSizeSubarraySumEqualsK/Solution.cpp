#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;
class Solution {
 public:
  int maxSubArrayLen(vector<int>& nums, int k) {
    // Initially thought of backtracking; but we want subarray, not a subseq.
    // Sliding window may be plausible. The naive one, which would involve
    // tracking a running sum is not plausible though, since its is not clear
    // when to shrink the window.
    // However, what about prefix sums? It allows us to query the sum of a
    // range. Something like two-sum but with ranges instead of individual
    // elements.
    // Hmm. Iterate through the array, calculating the prefix sum
    // nums[0..i] (inclusive).
    // Look for its complement, i.e., sum(nums[0..i]) - k.

    // {complement, index}
    std::unordered_map<long long, int> prefixSums;
    prefixSums[0] = -1;  // handle the case where sum(nums[0..i]) == k

    long long sum = 0;
    int maxSize = 0;
    for (int i = 0; i < nums.size(); ++i) {
      sum += nums[i];

      // We want sum(nums[0..i]) - sum(nums[0..j]) == k
      // Therefore, sum(nums[0..j]) = sum(nums[0..i]) - k
      auto iter = prefixSums.find(sum - static_cast<int>(k));
      if (iter != prefixSums.end()) {
        maxSize = std::max(maxSize, i - iter->second);
      }

      // hm. check if the prefix sum already exist. if it does, there is no
      // point inserting this one.
      if (!prefixSums.count(sum)) {
        prefixSums[sum] = i;
      }
    }
    return maxSize;
  }
};
