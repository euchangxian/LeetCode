#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

using namespace std;
class Solution {
 public:
  int partitionArray(std::vector<int>& nums, int k) {
    // Reduce the problem, again! The question may seem like it wants to
    // disallow sorting, by mentioning the definition of a subsequence.
    // But notice that the order of elements within each subsequence do not
    // matter. We only want the minimum and maximum of each subsequence such
    // that max - min <= k.
    // Therefore, sorting allows us to reduce this problem into a sliding window
    // question (a little modified, since we do not want all subarrays, but the
    // minimum number of subarrays), where the leftmost and rightmost of the
    // window differ by at most k.
    if (nums.empty()) {
      return 0;
    }

    std::sort(nums.begin(), nums.end());

    // start with a singular partition => the entire array.
    int partitions = 1;
    int l = 0;
    for (int r = 1; r < nums.size(); ++r) {
      // try to move r rightwards until the condition nums[r] - nums[l] <= k
      // is violated. Then we know that the elements in [l..r-1] belong to its
      // partition.
      if (nums[r] - nums[l] > k) {
        ++partitions;
        l = r;
      }
    }

    return partitions;
  }
};
