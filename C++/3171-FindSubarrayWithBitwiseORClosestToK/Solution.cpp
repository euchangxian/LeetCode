#include <algorithm>
#include <climits>
#include <cmath>
#include <vector>

class SegmentTree {
 public:
  SegmentTree(int n) : N(n), tree(4 * N, 0) {}

  SegmentTree(const std::vector<int>& nums) : SegmentTree(nums.size()) {
    build(nums, 1, 0, N - 1);
  }

  int query(int l, int r) const {
    return query_(1, 0, N - 1, l, r);  // todo
  }

 private:
  int N;
  std::vector<int> tree;

  static constexpr int left(int i) { return (i << 1); }
  static constexpr int right(int i) { return (i << 1) + 1; }
  static constexpr int merge(int l, int r) { return l | r; }

  void build(const std::vector<int>& nums, int idx, int L, int R) {
    if (L == R) {
      tree[idx] = nums[L];
      return;
    }

    int mid = (L + R) / 2;
    build(nums, left(idx), L, mid);
    build(nums, right(idx), mid + 1, R);
    tree[idx] = merge(tree[left(idx)], tree[right(idx)]);
  }

  int query_(int idx, int L, int R, int l, int r) const {
    if (l > r) {
      return 0;  // identity for |
    }

    if (l <= L && R <= r) {
      return tree[idx];
    }

    int mid = (L + R) / 2;
    return merge(query_(left(idx), L, mid, l, std::min(r, mid)),
                 query_(right(idx), mid + 1, R, std::max(l, mid + 1), r));
  }
};

class Solution {
 public:
  int minimumDifference(std::vector<int>& nums, int k) {
    const int n = nums.size();
    SegmentTree st(nums);

    int result = INT_MAX;
    for (int start = 0; start < n; ++start) {
      int left = start, right = n - 1;
      while (left <= right) {
        int mid = left + (right - left) / 2;

        int orSum = st.query(start, mid);
        result = std::min(result, std::abs(orSum - k));
        if (orSum <= k) {
          left = mid + 1;
        } else {
          right = mid - 1;
        }
      }
    }
    return result;
  }
};
