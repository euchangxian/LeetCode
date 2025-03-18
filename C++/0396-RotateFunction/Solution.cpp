#include <algorithm>
#include <vector>

class Solution {
 public:
  int maxRotateFunction(std::vector<int>& nums) {
    // Roate nums k positions clockwise.
    // Define P(nums) as i * nums[i] for i in 0..n-1
    // Determine max P(nums) after rotating
    // i.e., F(0) is the value obtained from rotating nums 0 times.
    //
    // Hmm. Larger numbers at the back. Smaller infront, to maximise i*nums[i].
    // Feels DP-like.
    // No clear strategy on ordering.
    //
    // Hm. Naively:
    // max at i=0: 0
    // max at i=1: max(nums[0], nums[1])
    // max at i=2: max(nums[1]+2*nums[2], nums[0]+2*nums[1], nums[2]+2*nums[0])
    // Essentially, for each new number introduced, there are k possible
    // positions it can be (each rotation)
    // O(N^2), brute force double for-loop
    //
    // WHERE is the recomputation of work?
    // Suppose F(0) is already computed. Can we obtain F(1) from F(0)?
    // Ah. We can.
    // Compute the sum of nums, Sum(nums)=nums[0] + nums[1] + .. + nums[n-1]
    // Given:
    // F(0) = 0*nums[0] + 1*nums[1] + ... + (n-1)*nums[n-1],
    // F(1) = 0*nums[n-1] + 1*nums[0] + 2*nums[1] + ... + (n-1)*nums[n-2]
    // F(1) - F(0) = nums[0] + nums[1] + ... + nums[n-2] - (n-1)*nums[n-1]
    // F(2)-F(1) = nums[0] + ... + nums[n-1] - (n-1)*nums[n-2]
    //
    // Thus, F(k) = F(k-1) + Sum(nums) - n*nums[n-k]
    // NOTE: we minus an extra nums[n-k], since Sum(nums) include nums[n-k]
    const int n = nums.size();

    int F = 0;
    int sum = 0;
    for (int i = 0; i < nums.size(); ++i) {
      F += i * nums[i];
      sum += nums[i];
    }

    int best = F;
    for (int k = 1; k < nums.size(); ++k) {
      F = F + sum - (n * nums[n - k]);
      best = std::max(best, F);
    }
    return best;
  }
};
