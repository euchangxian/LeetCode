#include <algorithm>
#include <array>
#include <vector>

constexpr int MAX_N = 1000;
class Solution {
 public:
  std::vector<int> findKDistantIndices(std::vector<int>& nums, int key, int k) {
    // a k-distant index is an index i of nums for which there exists at least
    // one index j such that | i - j | <= k, nums[j] == key.
    // Sorted in increasing order.
    // Naively (and sufficiently), just O(NK),  which tends to O(N^2).
    // Can we do better?
    // Note that we need nums[j] == key. So we can take the position of all
    // nums[j] == key.
    // Ah. Line Sweep. We can mark j-k and j+k
    auto n = static_cast<int>(nums.size());
    std::array<int, MAX_N + 1> line{};
    for (int i = 0; i < n; ++i) {
      if (nums[i] == key) {
        ++line[std::max(i - k, 0)];
        --line[std::min(i + k + 1, MAX_N)];  // exclusive
      }
    }

    int inRange = 0;
    std::vector<int> result;
    for (int i = 0; i < n; ++i) {
      inRange += line[i];

      if (inRange > 0) {
        result.push_back(i);
      }
    }
    return result;
  }
};
