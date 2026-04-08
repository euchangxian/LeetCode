#include <algorithm>
#include <functional>
#include <vector>

class Solution {
 public:
  int xorAfterQueries(std::vector<int>& nums,
                      std::vector<std::vector<int>>& queries) {
    // nums of size n, queries of size q.
    // queries[i] = [l, r, k, v]
    // for each query:
    // - set idx=l
    // - while idx <= r:
    //   - update: nums[idx] = (nums[idx] * v) % (10^9 + 7)
    //   - set   : idx += k
    // Return the bitwise XOR of all elements in nums after all queries.
    //
    // XOR is associative: we can reorder it. But does it matter?
    // Update at [idx, idx+k, idx+2k, ...]
    // O(n^3) though.
    // Can we do better other than simulation?
    constexpr int MOD = 1E9 + 7;
    constexpr auto modPow = [](auto n, auto exp) {
      long long result = 1;
      long long base = n;
      for (; exp > 0; exp >>= 1) {
        if (exp & 1) {
          result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
      }
      return result;
    };

    for (const auto& q : queries) {
      auto l = q[0];
      auto r = q[1];
      auto k = q[2];
      auto v = q[3];

      for (; l <= r; l += k) {
        nums[l] = (static_cast<long long>(nums[l]) * v) % MOD;
      }
    }

    return std::ranges::fold_left(nums, 0, std::bit_xor<>{});
  }
};
