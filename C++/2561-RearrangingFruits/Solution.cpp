#include <algorithm>
#include <cmath>
#include <limits>
#include <ranges>
#include <unordered_map>
#include <vector>

using i64 = long long;
class Solution {
 public:
  i64 minCost(std::vector<int>& basket1, std::vector<int>& basket2) {
    // basket1 and basket2 of n fruits each.
    // As many times:
    // - Choose two indices i, j, swap basket1[i] with basket2[j].
    // - Cost of the swap is min(basket1[i], basket2[j])
    // Two baskets are equal if they contain the exact same fruit costs after
    // sorting them.
    // Return the minimum cost or -1 if impossible.
    //
    // Hm. We can determine if impossible, if there is an odd instance of a
    // certain value.
    // i.e., basketx[k] = 100 occurs only once in total.
    //
    // There is an upper-bound on the number of swaps required to make them
    // equal which is n - both baskets have different set of distinct elements,
    // non-overlapping.
    // Though, this is not necessarily the lowest cost. E.g.,
    // basket1 = [1, 1, 100, 100]
    // basket2 = [200, 200, 300, 300]
    // Doing "naive" greedily, we have swap(1, 300) + swap(100, 200) = 101-cost
    // But if we move '1' back-and-forth, we can have:
    // swap(1, 300) + swap(100, 1) + swap(1, 200) = 3-cost
    // Thus if swapping a number twice is better, then that is our less-"naive"
    // greedy.
    auto n = static_cast<int>(basket1.size());
    std::unordered_map<int, int> frequency;
    i64 minVal = std::numeric_limits<i64>::max();
    for (auto [a, b] : std::views::zip(basket1, basket2)) {
      ++frequency[a];
      --frequency[b];
      minVal = std::min(minVal, static_cast<i64>(std::min(a, b)));
    }

    std::vector<int> toSwap;
    for (auto [val, freq] : frequency) {
      if (freq % 2) {
        return -1LL;
      }

      for (int i = 0; i < std::abs(freq) / 2; ++i) {
        toSwap.push_back(val);
      }
    }

    // Intermediate value for swapping
    auto pairs = static_cast<int>(toSwap.size() / 2);
    std::nth_element(toSwap.begin(), toSwap.begin() + pairs, toSwap.end());
    i64 result = 0;
    for (i64 x : toSwap | std::views::take(pairs)) {
      result += std::min(minVal * 2, x);
    }
    return result;
  }
};
