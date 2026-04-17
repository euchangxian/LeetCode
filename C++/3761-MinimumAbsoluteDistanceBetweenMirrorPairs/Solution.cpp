#include <algorithm>
#include <unordered_map>
#include <utility>
#include <vector>

class Solution {
 public:
  int minMirrorPairDistance(std::vector<int>& nums) {
    // A mirror pair is a pair of indices (i, j):
    // - 0 <= i < j < n, and
    // - reverse(nums[i]) == nums[j] where reverse(x) reverses the decimal
    //   digits, dropping leading zeroes.
    // Return the minimum distance between indices of any mirror pair,
    // or -1.
    //
    // One-pass: Maintain the latest index of reverse(x), then calculate
    // the distance on every match between {reverse(x), y}.
    // nums[i] <= 1E9 => std::unordered_map necessary.
    constexpr auto reverse = [](auto x) {
      auto reversed = 0;
      while (x) {
        auto d = x % 10;
        x /= 10;
        reversed = reversed * 10 + d;
      }
      return reversed;
    };
    const auto n = static_cast<int>(nums.size());

    int result = n;
    std::unordered_map<int, int> lastSeen;
    lastSeen.reserve(n);
    for (int i = 0; i < n; ++i) {
      auto y = nums[i];
      if (auto it = lastSeen.find(y); it != lastSeen.end()) {
        result = std::min(result, i - it->second);
      }
      lastSeen[reverse(y)] = i;
    }

    return result == n ? -1 : result;
  }
};
