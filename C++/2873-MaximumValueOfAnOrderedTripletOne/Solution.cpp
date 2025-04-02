#include <algorithm>
#include <vector>

using i64 = long long;

class Solution {
 public:
  i64 maximumTripletValue(std::vector<int>& nums) {
    // Maximum value over all triplets of all indices (i, j, k), i < j < k.
    // Value of a triplet (i, j, k) is (nums[i] - nums[j]) * nums[k]
    //
    // Lmao. See 2874.
    i64 result = 0;

    i64 maxNum = 0;
    i64 maxDiff = 0;
    for (i64 num : nums) {
      result = std::max(result, maxDiff * num);

      maxDiff = std::max(maxDiff, maxNum - num);
      maxNum = std::max(maxNum, num);
    }

    return result;
  }
};
