#include <algorithm>
#include <cstdlib>
#include <vector>

class SegmentTree {
 public:
  SegmentTree(int n) : N(n), tree(4 * N, 0) {}

  int query(int l, int r) const { return query_(1, 0, N - 1, l, r); }

  void update(int pos, int val) { update_(1, 0, N - 1, pos, val); }

 private:
  const int N;
  std::vector<int> tree;

  static constexpr int left(int i) { return i << 1; }
  static constexpr int right(int i) { return (i << 1) + 1; }

  int query_(int idx, int L, int R, int l, int r) const {
    if (l > r) {
      return 0;
    }

    if (l <= L && R <= r) {
      return tree[idx];
    }

    int mid = (L + R) / 2;
    return std::max(query_(left(idx), L, mid, l, std::min(r, mid)),
                    query_(right(idx), mid + 1, R, std::max(l, mid + 1), r));
  }

  void update_(int idx, int L, int R, int pos, int val) {
    if (L == R) {
      tree[idx] = val;
      return;
    }

    int mid = (L + R) / 2;
    if (pos <= mid) {
      update_(left(idx), L, mid, pos, val);
    } else {
      update_(right(idx), mid + 1, R, pos, val);
    }

    tree[idx] = std::max(tree[left(idx)], tree[right(idx)]);
  }
};

class Solution {
 public:
  int lengthOfLIS(std::vector<int>& nums, int k) {
    // Find the longest increasing subsequence, with an extra constraint:
    // - The difference between adjacent elements is at most k.
    //
    // LIS/Patience Solitaire does not seem to work trivially.
    // Hm. When we encounter a new element, how can we decide whether we can
    // extend an existing subsequence, or start a new subsequence?
    //
    // Seems very similar to 673-Number of Longest Increasing Subsequence,
    // where the maximum length of the subsequence ending at an index is tracked
    // in a PURQ Fenwick/Segment Tree (discretization of values is done to
    // enable querying for smaller values).
    //
    // Are we able to do the same here? With Range Maximum Queries from the
    // values [x-k, x] to respect the "difference at most k" constraint.
    // Seems too trivial??
    // Ah, after discretizing, its not straightforward to do x-k.
    // Therefore, need to insert x-k into the discretization too.
    //
    // NOTE:
    // Skipping the discretization will have a massive speed up.
    const int maxVal = *std::max_element(nums.begin(), nums.end());
    SegmentTree st(maxVal + 1);
    int result = 0;
    for (int num : nums) {
      // extend the LIS
      int lis = st.query(num - k, num - 1) + 1;

      result = std::max(result, lis);
      st.update(num, lis);
    }

    return result;
  }
};
