#include <algorithm>
#include <vector>

class Solution {
 public:
  std::vector<int> maxValue(std::vector<int>& nums) {
    // From any index i, jump to another index j:
    // - j>i: if nums[j] < nums[i]
    // - j<i: if nums[j] > nums[i]
    // For each index i, find the maximum value in nums that can be reached by
    // following any sequence of valid jumps starting at i.
    // Return ans[i] = max reachable nums[j] starting from i.
    //
    // - jump forward if destination value is lower
    // - jump backward if destination value is higher
    //
    // Can there be an optimal path to jump forward, then backwards?
    // Or vice-versa?
    // Yes. See example.
    // nums = [2, 3, 1]
    // From i=0 -> j=2 -> j->1
    //
    // Naively, it's graph like. Directed graphs where edges represent valid
    // jumps.
    // Seems to be prefix/suffix min/max?
    // Not exactly. The max value may not be reachable -> need second max,
    // third, etc.
    // Not exactly too: we do not care about the suffix max.
    // We jump to the suffix min, and get its prefix max.
    // We need to traverse from rightmost.
    const auto n = static_cast<int>(nums.size());

    std::vector<int> pmax(n);
    pmax[0] = nums[0];
    for (int i = 1; i < n; ++i) {
      pmax[i] = std::max(nums[i], pmax[i - 1]);
    }

    // reuse nums for smin
    auto& smin = nums;
    for (int i = n - 2; i >= 0; --i) {
      smin[i] = std::min(nums[i], smin[i + 1]);
    }

    std::vector<int> result(n);
    result[n - 1] = pmax[n - 1];
    for (int i = n - 2; i >= 0; --i) {
      if (pmax[i] > smin[i + 1]) {
        // merge segment
        result[i] = result[i + 1];
      } else {
        // new segment
        result[i] = pmax[i];
      }
    }
    return result;
  }
};
