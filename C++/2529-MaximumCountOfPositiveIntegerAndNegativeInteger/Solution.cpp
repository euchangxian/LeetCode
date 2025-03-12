#include <algorithm>
#include <vector>

class Solution {
 public:
  int maximumCount(std::vector<int>& nums) {
    // nums is sorted in non-decreasing order.
    // Therefore, nums would look something like:
    // [-, -, -, 0, 0, 0, +, +, +]
    //           ^        ^
    //           lb       ub

    // find first 0.
    auto lb = std::lower_bound(nums.begin(), nums.end(), 0);

    // find last 0
    auto ub = std::upper_bound(nums.begin(), nums.end(), 0);

    // nums.end() is already 1-indexed, while ub is 0-indexed. No need to +1.
    // Similarly, lb is pointing to 1-past the largest negative number. No
    // need to +1.
    return std::max(nums.end() - ub, lb - nums.begin());
  }

  int maximumCountNaive(std::vector<int>& nums) {
    int pos = 0;
    int neg = 0;

    for (int num : nums) {
      pos += num > 0;
      neg += num < 0;
    }
    return std::max(pos, neg);
  }
};
