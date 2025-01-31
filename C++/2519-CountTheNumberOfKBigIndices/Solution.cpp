#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

class FenwickTree {
 public:
  FenwickTree(int n) : N(n), tree(N + 1, 0) {}

  int query(int l, int r) const { return query_(r) - query_(l - 1); }

  void update(int i, int diff) {
    for (; i <= N; i += (i & -i)) {
      tree[i] += diff;
    }
  }

  int query_(int i) const {
    int sum = 0;
    for (; i > 0; i -= (i & -i)) {
      sum += tree[i];
    }
    return sum;
  }

  void reset() { std::fill(tree.begin(), tree.end(), 0); }

 private:
  const int N;
  std::vector<int> tree;
};

class Solution {
 public:
  int kBigIndices(std::vector<int>& nums, int k) {
    // An index i is k-big if:
    // - there exists at least k different indices idx1, such that
    //   idx1 < i, and nums[idx1] < nums[i], AND
    // - there exists at least k different indices idx2, such that
    //   idx2 > i, and nums[idx2] < nums[i].
    //
    // left-to-right, find idx1 < i. Use Fenwick Trees to query smaller.
    // right-to-left, find idx2 > i. Use another Fenwick Tree to query smaller.
    const int n = nums.size();
    const int maxVal = *std::max_element(nums.begin(), nums.end());

    FenwickTree ft(maxVal + 1);
    std::vector<int> idx1(n, 0);
    for (int i = 0; i < n; ++i) {
      idx1[i] = ft.query(1, nums[i]);

      ft.update(nums[i] + 1, 1);
    }

    ft.reset();
    std::vector<int> idx2(n, 0);
    for (int i = n - 1; i >= 0; --i) {
      idx2[i] = ft.query(1, nums[i]);

      ft.update(nums[i] + 1, 1);
    }

    int count = 0;
    for (int i = 0; i < n; ++i) {
      if (idx1[i] >= k && idx2[i] >= k) {
        ++count;
      }
    }
    return count;
  }
};
