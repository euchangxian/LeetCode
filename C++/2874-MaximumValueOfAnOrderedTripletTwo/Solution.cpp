#include <algorithm>
#include <vector>

using i64 = long long;
class Solution {
 public:
  i64 maximumTripletValue(std::vector<int>& nums) {
    const int n = nums.size();

    i64 result = 0;   // best (nums[i]-nums[j]) * nums[k]
    i64 maxNum = 0;   // best nums[i]
    i64 maxDiff = 0;  // best nums[i] - nums[j]
    for (i64 num : nums) {
      result = std::max(result, maxDiff * num);

      // NOTE: We update nums[i] - nums[j] before updating nums[i]
      // i.e., avoid doing nums[j] - nums[j] (maxNum is updated to nums[j])
      maxDiff = std::max(maxDiff, maxNum - num);
      maxNum = std::max(maxNum, num);
    }

    return result;
  }

  i64 maximumTripletValueThreePass(std::vector<int>& nums) {
    // Value of an ordered triplet (i, j, k) is (nums[i]-nums[j]) * nums[k]
    // We want to maximise the value of nums[i]-nums[j], and nums[k].
    //
    // Iterate over j:
    // - To get nums[k], suffixMax.
    // - To get nums[i], pick prefixMax
    const int n = nums.size();
    std::vector<int> left(n), right(n);
    left[0] = right[n - 1] = 0;
    for (int i = 1; i < n; ++i) {
      left[i] = std::max(left[i - 1], nums[i - 1]);
    }

    // Technically, with some indexing manipulation and an bounds-check, can
    // be done in 1-pass with calculation of left[i]
    for (int i = n - 2; i >= 0; --i) {
      right[i] = std::max(right[i + 1], nums[i + 1]);
    }

    i64 result = 0;
    for (int j = 1; j < n - 1; ++j) {
      result = std::max(result, (1LL * left[j] - nums[j]) * right[j]);
    }
    return result;
  }
};
