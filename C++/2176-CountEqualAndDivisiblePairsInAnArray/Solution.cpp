#include <vector>

constexpr int MAX_N = 100;
class Solution {
 public:
  int countPairs(std::vector<int>& nums, int k) {
    // Return the number of pairs (i, j), i < j such that
    // - nums[i] == nums[j], and
    // - (i * j) % k == 0
    // (i * j) % k = ((i % k) * (j % k)) % k = 0
    // For this small constraint n<=100, an O(N^2) loop will suffice.
    const int n = nums.size();
    int count = 0;
    for (int j = 1; j < n; ++j) {
      for (int i = 0; i < j; ++i) {
        count += ((i * j) % k == 0 && nums[i] == nums[j]);
      }
    }
    return count;
  }
};
