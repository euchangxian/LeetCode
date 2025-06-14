#include <algorithm>
#include <vector>

class Solution {
 public:
  int minimizeMax(std::vector<int>& nums, int p) {
    // Find p pairs of indices of nums such that the maximum difference amongst
    // all the pairs is minimized.
    // Each index should appear at most once.
    //
    // n <= 1e5
    // Naive O(N^2) wouldnt work.
    // Though, differences are minimised between adjacent values in sorted
    // order.
    // Sort.
    // Then, heap? Not easy to determine whether a number should be paired with
    // its left or right neighbour.
    // Does this choice matter?
    // Trivially, nums = [1, 100, 101], p=1
    // Choice...
    //
    // Lol. Looked at hints. BSTA on max difference.
    const int n = nums.size();
    std::ranges::sort(nums);

    auto feasible = [&](int maxDiff) {
      int pairs = 0;
      for (int i = 1; i < n && pairs < p; ++i) {
        if (nums[i] - nums[i - 1] <= maxDiff) {
          ++pairs;
          ++i;
        }
      }
      return pairs >= p;
    };

    int left = 0;
    int right = nums.back() - nums.front();
    while (left < right) {
      int mid = left + (right - left) / 2;

      if (feasible(mid)) {
        // look for smaller threshold
        right = mid;
      } else {
        left = mid + 1;
      }
    }
    return left;
  }
};
