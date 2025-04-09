#include <algorithm>
#include <bitset>
#include <limits>
#include <vector>

constexpr int MAX_VAL = 100;
class Solution {
 public:
  int minOperations(std::vector<int>& nums, int k) {
    // An integer h is called valid if all the values that are strictly greater
    // than h are identical.
    // In each operation:
    // - Select an integer h that is valid
    // - For each nums[i] > h, set nums[i] = h.
    // Find minimum operations to make every element in nums equal to k, or
    // -1 if impossible.
    //
    // Impossible to increase the value of nums[i], i.e., k is the minimum value
    // in nums.
    // Wait. Not exactly. K must be <= min. The operation can be applied to
    // min.
    //
    // Naively, keep track of the frequency of the values.
    // Starting from the 2nd-largest, an operation is required. Thus, the number
    // of operations is H-1, where H is the number of unique values.
    std::bitset<MAX_VAL + 1> seen{};

    int min = std::numeric_limits<int>::max();
    for (int num : nums) {
      min = std::min(min, num);
      seen[num] = 1;
    }

    if (k > min) {
      return -1;
    }

    // An extra operation is required if min > k, to set min == k.
    return seen.count() - (k == min);
  }
};
