#include <algorithm>
#include <limits>
#include <unordered_map>
#include <utility>
#include <vector>

class Solution {
 public:
  int maximumBeauty(std::vector<int>& flowers) {
    // Garden of n flowers.
    // flowers[i] represent the beauty of the ith flower.
    // A garden is valid if:
    // 1. Garden has at least two flowers
    // 2. The first and last flower have the same beauty value.
    // The beauty of a garden is the sum of beauty of all remaining flowers.
    // Remove any number of numbers such that the garden is valid, and the
    // beauty is maximum.
    // Given that flowers[i] can be negative, simply taking the furthest
    // flowers[l] == flowers[r] will not work.
    //
    // Also, note the constraints: -10^4 <= flowers[i] <= 10^4
    // This does imply that a solution based on values is possible
    //
    // Naively, for each flowers[i] = x, find all the corresponding j != i,
    // flowers[j] == x, then determine the sum of the subarray from flowers[i]
    // to flowers[j].
    // Intuitively, the repeated work comes from repeatedly summing the subarray
    // sum. Can be alleviated with prefix sums, range sum queries in O(1) time.
    // - 1 pass to collect all indices of a certain value, and compute prefix
    //   sums. O(N).
    // - O(N^2) to iterate over all possible pairs of indices to determine the
    //   maximum range sum.
    // Wait. Lol. There is a misunderstanding in the operations to be applied.
    // We can remove negative flowers IN-BETWEEN too. Thus, we simply need
    // the left-most and right-most index of a beauty value, removing all
    // negatives in between.
    // Dynamic RSQs?
    // Just greedily remove negatives from our prefix precomputation.

    // Determine first and last position of each beauty value.
    // NOTE: A hashmap may be better, considering the sparse-ness of pairs.
    // std::array<int, MAX_VAL * 2 + 1> left, right;
    // std::memset(left.data(), -1, sizeof(left));
    // std::memset(right.data(), -1, sizeof(right));
    const int n = flowers.size();
    std::vector<int> prefix(n + 1);
    prefix[0] = 0;

    std::unordered_map<int, int> first, pairs;
    first.reserve(n), pairs.reserve(n);
    for (int i = 0; i < n; ++i) {
      prefix[i + 1] = prefix[i];
      if (flowers[i] > 0) {
        // Only include in the prefix sum if positive.
        prefix[i + 1] += flowers[i];
      }

      auto it = first.find(flowers[i]);
      if (it == first.end()) {
        // only take the first
        first.emplace(flowers[i], i);
      } else {
        // always take the last
        int l = it->second;
        pairs[l] = i;
      }
    }

    int result = std::numeric_limits<int>::min();
    for (const auto [l, r] : pairs) {
      int rangeSum = prefix[r + 1] - prefix[l];
      if (flowers[l] < 0) {
        // The negatives are not included in the computation of prefix sums,
        // yet may be necessary in the case where the only valid start/ends
        // are negatives.
        result = std::max(result, flowers[l] + flowers[r] + rangeSum);
      } else {
        result = std::max(result, rangeSum);
      }
    }
    return result;
  }
};
