#include <cstddef>
#include <cstdlib>
#include <ranges>
#include <utility>
#include <vector>

using i64 = long long;

class FenwickTree {
 public:
  FenwickTree(int n) : n(n), tree(n + 1, 0) {}

  int query(int l, int r) const { return prefix(r) - prefix(l - 1); }

  void update(int i, int diff) {
    for (; i <= n; i += i & -i) {
      tree[i] += diff;
    }
  }

  int prefix(int i) const {
    int sum = 0;
    for (; i > 0; i -= i & -i) {
      sum += tree[i];
    }
    return sum;
  }

 private:
  const int n;
  std::vector<int> tree;
};

class Solution {
 public:
  long long numberOfPairs(std::vector<int>& nums1,
                          std::vector<int>& nums2,
                          int diff) {
    // Find number of ordered pairs (i, j) such that:
    // - nums1[i] - nums1[j] <= nums2[i] - nums2[j] + diff
    // Hm, try to reduce:
    //   nums1[i] - nums2[i] <= nums1[j] - nums2[j] + diff
    //
    // Then, its pretty simple already. Do nums1 - nums2,
    // then, iterating from the left, since we want ordered pairs:
    // given target = nums1[j] - nums2[j] + diff,
    // do a prefix query on [1..target-1]
    //
    // Fenwick Trees will suffice.
    // Discretization is necessary since nums1[i] - nums2[i] >= -10^4
    // Or rather, shift the sums.
    // negative 3*10^4 to 3*10^4
    constexpr int SHIFT = 3 * 10'000;
    const std::vector<int> combined =
        std::ranges::views::zip(nums1, nums2) |
        std::ranges::views::transform([](const std::pair<int, int>& p) -> int {
          return p.first - p.second;
        }) |
        std::ranges::to<std::vector<int>>();

    // negative 3*10^4 to 3*10^4
    FenwickTree ft(2 * SHIFT + 1);
    i64 count = 0LL;
    for (int num : combined) {
      count += ft.prefix(num + diff + SHIFT + 1);
      ft.update(num + SHIFT + 1, 1);
    }
    return count;
  }
};
