#include <algorithm>
#include <array>
#include <cstdint>
#include <vector>

class Solution {
 public:
  int largestInteger(std::vector<int>& nums, int k) {
    // x is almost missing from nums if x appears in exactly one subarray of
    // size k within nums.
    // Return the largest almost missing integer, or -1.
    //
    // WTF. Pigeonhole principle.
    // k=1     => largest unique
    // k=n     => largest element
    // 1<=k<=n => Every integer (NOT element) EXCEPT the first and last element
    //            WILL be covered by at least 2 subarrays (visualise).
    const auto n = static_cast<int>(nums.size());
    if (k == n) {
      return std::ranges::max(nums);
    }

    constexpr auto MAX_VAL = 50;
    std::array<std::uint8_t, MAX_VAL + 1> freq{};
    for (auto x : nums) {
      ++freq[x];
    }
    if (k == 1) {
      for (auto i = MAX_VAL; i >= 1; --i) {
        if (freq[i] == 1) {
          return i;
        }
      }
    }

    auto valid = [&freq](auto x) { return freq[x] == 1 ? x : -1; };
    return std::max(valid(nums.front()), valid(nums.back()));
  }
};
