#include <array>
#include <cstdint>
#include <vector>

class Solution {
 public:
  bool isGood(std::vector<int>& nums) {
    // An array is good if it is a permutation of an array base[n].
    // base[n] = [1, 2, ..., n-1, n, n]: array of length n+1, contains 1..n-1
    // exactly once, and two occurences of n.
    // Return true if good.
    constexpr auto MAX_VAL = 200;
    const auto n = static_cast<int>(nums.size()) - 1;
    if (n <= 0) {
      return false;
    }
    std::array<std::uint8_t, MAX_VAL + 1> freq{};
    for (auto x : nums) {
      if (x > n) {
        return false;
      }

      ++freq[x];
      if (x < n && freq[x] > 1) {
        return false;
      }
      if (x == n && freq[x] > 2) {
        return false;
      }
    }

    return true;
  }
};
