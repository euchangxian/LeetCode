#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iterator>
#include <vector>

using i64 = long long;

class FenwickTree {
 public:
  FenwickTree(const int n) : N(n), tree(n + 1, 1) {
    for (int i = 1; i <= N; ++i) {
      int parent = i + (i & -i);

      if (parent <= N) {
        tree[parent] += tree[i];
      }
    }
  }

  i64 query(int l, int r) const { return query_(r) - query_(l - 1); }

  i64 query_(int i) const {
    i64 sum = 0;
    for (; i > 0; i -= (i & -i)) {
      sum += tree[i];
    }
    return sum;
  }

  void update(int i, i64 diff) {
    for (; i <= N; i += (i & -i)) {
      tree[i] += diff;
    }
  }

 private:
  const int N;
  std::vector<i64> tree;
};

class Solution {
 public:
  int countRangeSum(std::vector<int>& nums, int lower, int upper) {
    // Find the number of range sums that lie in [lower, upper] inclusive.
    // Enumerate all possible range sums? O(n^2).
    //
    // The key to this is reducing the equation.
    //
    // - sum(l, r) = sum(1, r) - sum(1, l)
    //             = x - y
    // Therefore, for each prefix sum x, we want to find how many previous
    // prefix sums y satisfy:
    // - lower ≤ x - y ≤ upper
    // Rearranging, we get: upper <= y - x <= lower
    //                      x + upper <= y <= x + lower
    //
    // - x+lower >= y (std::lower_bound)
    // - x+upper <= y (std::upper_bound - 1)
    // In other words, for each current sum x, we are looking for the number of
    // previous prefix sums y that satisfy the equation.
    //
    // Thus, we can discretize the prefix sums first.
    // Iterating over each sum, find the number of prefix sums within the range
    // (x+lower, x+upper), excluding the current sum to avoid over-counting.
    const int n = nums.size();
    std::vector<i64> prefix(n + 1);
    prefix[0] = 0;
    for (int i = 1; i <= n; ++i) {
      prefix[i] = prefix[i - 1] + nums[i - 1];
    }

    // discretization. No need to handle duplicates, since
    // std::lower/upper_bound will be used to find the corresponding index.
    std::vector<i64> rank = prefix;
    std::sort(rank.begin(), rank.end());

    FenwickTree ft(rank.size());
    int count = 0;
    for (const i64 x : prefix) {
      int idx = std::distance(rank.begin(),
                              std::lower_bound(rank.begin(), rank.end(), x)) +
                1;
      ft.update(idx, -1);

      int lowerBound =
          std::distance(rank.begin(),
                        std::lower_bound(rank.begin(), rank.end(), x + lower)) +
          1;
      int upperBound = std::distance(
          rank.begin(), std::upper_bound(rank.begin(), rank.end(), x + upper));

      count += ft.query(lowerBound, upperBound);
    }
    return count;
  }
};
