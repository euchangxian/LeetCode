#include <algorithm>
#include <array>
#include <vector>

constexpr int MAX_N = 1E5;

class Solution {
 public:
  int totalFruit(std::vector<int>& fruits) {
    // 0 <= fruits[i] <= fruits.length which represent the type of fruit the
    // ith tree produces.
    // Collect as many fruits as possible:
    // - Only two baskets, each basket can hold a single type of fruits without
    //   limit.
    // - Start from a tree of choice, pick exactly one fruit from every tree
    //   WHILE moving to the right.
    // - Move right until a fruit cannot be picked.
    //
    // Contiguous Subarrays of maximum two integers.
    auto n = static_cast<int>(fruits.size());

    std::array<int, MAX_N + 1> freq{};

    int unique = 0;
    int result = 0;
    for (int l = 0, r = 0; r < n; ++r) {
      if (freq[fruits[r]]++ == 0) {
        ++unique;
      }

      while (unique > 2) {
        if (--freq[fruits[l++]] == 0) {
          --unique;
        }
      }
      result = std::max(result, r - l + 1);
    }
    return result;
  }
};
