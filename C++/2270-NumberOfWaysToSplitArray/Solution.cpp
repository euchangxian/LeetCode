#include <cstddef>
#include <cstdlib>
#include <functional>
#include <numeric>
#include <vector>

class Solution {
 public:
  int waysToSplitArray(std::vector<int>& nums) {
    // a split is valid if:
    // - sum of first i+1 elements >= sum of last n-i+1 elements.
    // - at least one element to the right of the ith element, i.e., non-empty
    // splits.
    //
    // Hm. Iterate over all possible splitting points, check if its valid. At
    // most n-1 valid splits _ _ _ (non-empty)
    // Precompute prefix sums to obtain sum of splits efficiently.
    // sum(left) = prefix[i+1] - prefix[0]
    // sum(right) = prefix[n+1] - prefix[i+1]
    // Can be done with constant space. Note that we only need the total sum.
    // Assign this sum to the right subarray first.
    // Then, iterate over splits, include i in left subarray => exclude i in
    // right subarray.
    using i64 = long long;
    i64 rightSum = std::reduce(nums.begin(), nums.end(), 0LL, std::plus<>{});
    i64 leftSum = 0LL;

    int count = 0;
    // split after index i: left includes nums[i]
    for (int i = 0; i < nums.size() - 1; ++i) {
      leftSum += nums[i];
      rightSum -= nums[i];

      count += (leftSum >= rightSum);
    }
    return count;
  }
};
