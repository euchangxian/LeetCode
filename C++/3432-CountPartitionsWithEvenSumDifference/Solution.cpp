#include <algorithm>
#include <vector>

class Solution {
 public:
  int countPartitions(std::vector<int>& nums) {
    // A partition is an index i where 0<=i<n-1, splitting the array into
    // two non-empty subarrays, such that:
    // - Left subarray contains indices [0..i]
    // - Right subarray contains indices [i+1..n-1]
    // Return the number of partitions where the difference between the sum
    // of the left and right subarrays is even.
    //
    // Hm. Prefix?
    // Hm. Two passes? One to get the total sum. Then, starting at i=0,
    // consider two things:
    // - the parity of the initial sum of both subarrays nums[0] and
    // nums[1..n-1],
    // - the parity of nums[i] (nums[1])
    // Wait. Moving an odd number from left to right changes the difference by
    // an even number. left - x, right + x, diff = 2x
    // Moving an even number is the same.
    // So it all depends on the initial parity.
    // i.e., nums[0] and nums[1..n-1].
    // If odd difference => 0 valid partitions.
    // If even difference => n-1 valid partitions.
    //
    // Ah. In fact, we just need to check the total sum...
    const auto n = static_cast<int>(nums.size());
    if (auto sum = std::ranges::fold_left(nums, 0, std::plus<>{}); sum & 1) {
      return 0;
    }
    return n - 1;
  }
};
