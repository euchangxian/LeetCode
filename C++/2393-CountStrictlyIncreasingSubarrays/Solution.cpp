#include <cstddef>
#include <vector>

using namespace std;
class Solution {
 public:
  long long countSubarrays(vector<int>& nums) {
    // First glance, looks like Sliding Window?
    // 1, 3, 5, 4, 4, 6
    // ^        ^          count += 1 + 2 + 3 = 6
    //          ^  ^       count += 1
    //             ^    ^  count += 1 + 2 = 2
    // Seem to be 1 + 2 + ... + (r-l).
    // Hmmmmmm. What about thinking it in this way:
    // nums          = 1, 3, 5, 4, 4, 6
    // numIncreasing = 1  2  3  1  1  2
    // Where the number of increasing subarrays seem to restart to 1.

    long long sum = 1;
    long long numIncreasing = 1;
    for (size_t i = 1; i < nums.size(); ++i) {
      if (nums[i] <= nums[i - 1]) {
        numIncreasing = 0;  // restart
      }
      ++numIncreasing;
      sum += numIncreasing;
    }
    return sum;
  }
};
