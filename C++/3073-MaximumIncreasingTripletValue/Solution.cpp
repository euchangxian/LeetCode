#include <algorithm>
#include <set>
#include <vector>

class Solution {
 public:
  int maximumTripletValue(std::vector<int>& nums) {
    // Find (i, j, k) such that i < j < k and nums[i] < nums[j] < nums[k]
    // The value of a triplet (i, j, k) is nums[i] - nums[j] + nums[k]
    // We want to minimize nums[i]-nums[j], and maximise nums[k].
    //
    // Naive suffix min/max of nums[i] will not preserve j < k.
    //
    // Ah. Iterate over j instead of i.
    // Then, we can preprocess nums to get right[j] = suffixMax
    // Then, maintain an ordered set of prefixes, such that at index j,
    // we can find the largest nums[i] < nums[j].
    //
    // Ah. Not suffixMax. We need nums[j] < nums[k].
    // Monotonic stack.
    const int n = nums.size();

    std::vector<int> right(n, -1);
    int currMax = 0;
    for (int i = n - 1; i >= 0; --i) {
      if (nums[i] < currMax) {
        right[i] = currMax;
      } else {
        currMax = nums[i];
      }
    }

    int ans = 0;
    std::set<int> prefix{nums[0]};
    for (int j = 1; j < n - 1; ++j) {
      auto it = prefix.lower_bound(nums[j]);
      if (it != prefix.begin() && right[j] != -1) {
        int l = *(--it);
        int r = right[j];
        ans = std::max(ans, l - nums[j] + r);
      }

      prefix.insert(nums[j]);
    }
    return ans;
  }
};
