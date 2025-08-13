#include <array>
#include <bit>
#include <vector>

constexpr int MOD = 1E9 + 7;
constexpr int UB = 31 * 32 / 2;

constexpr std::array<int, UB> twoToPowerOf = []() {
  std::array<int, UB> result{};
  result[0] = 1;
  for (int i = 1; i < UB; ++i) {
    result[i] = (static_cast<long long>(result[i - 1]) << 1) % MOD;
  }
  return result;
}();

class Solution {
 public:
  std::vector<int> productQueries(int n,
                                  std::vector<std::vector<int>>& queries) {
    // Given positive integer n => 0-indexed array powers that consist of the
    // minimum number of powers of 2 that sum to N, sorted in non-decreasing.
    // Only one way to form this powers array.
    // Given queries[i] = [left, right] where for each query, the product of
    // all powers[j] must be answered, left <= j <= right, mod 1E9+7
    //
    // Okay, first, the elements in the powers array.
    // They can be obtained by inspecting the set bits of n, where each set bit
    // correspond to each element, and guarantees the minimum set.
    //
    // For range queries, a Segment Tree? Can we avoid a Seg Tree?
    // Given that we have powers of 2s only, i.e., all elements have the same
    // base-2.
    // Then, taking the product of these elements is equal to summing their
    // powers.
    // Therefore, we can use a Fenwick Tree!
    // Even better, we just need prefix sums.
    //
    // For obtaining the product efficiently, we can precompute the modded
    // powers of 2s. The range is at most 1 + 2 + ... + 31. (loose upper-bound)
    auto k = std::popcount(static_cast<unsigned int>(n));
    std::vector<int> powers = [k](unsigned int n) {
      std::vector<int> powers;
      powers.reserve(k);
      for (int i = 0; i < 32; ++i, n >>= 1) {
        if (n & 1) {
          powers.emplace_back(i);
        }
      }
      return powers;
    }(n);

    std::vector<int> prefix = [k, &powers]() {
      std::vector<int> prefix(k + 1);
      prefix[0] = 0;
      for (int i = 1; i <= k; ++i) {
        prefix[i] = prefix[i - 1] + powers[i - 1];
      }
      return prefix;
    }();

    std::vector<int> result;
    result.reserve(queries.size());
    for (const auto& q : queries) {
      int l = q[0];
      int r = q[1];
      int power = prefix[r + 1] - prefix[l];
      result.emplace_back(twoToPowerOf[power]);
    }
    return result;
  }
};
