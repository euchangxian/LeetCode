#include <algorithm>
#include <climits>
#include <cmath>
#include <vector>

class SegmentTree {
 public:
  SegmentTree(int n) : N(n), tree(4 * N, INT_MAX) {}

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
  static constexpr int merge(int l, int r) { return l & r; }

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
      return INT_MAX;  // identity for &
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
  int closestToTarget(std::vector<int>& arr, int target) {
    // Note that the AND sum is monotonically non-increasing.
    // Thus, we can binary search our right range for the value closest to
    // target.
    // if val > target, we increment r
    // else decrement r
    // Hm. What about l.
    // Not simple.
    // What if we try all starting positions of l.
    const int n = arr.size();
    SegmentTree st(arr);

    int result = INT_MAX;
    for (int start = 0; start < n; ++start) {
      int left = start, right = n - 1;
      while (left <= right) {
        int mid = left + (right - left) / 2;
        int andSum = st.query(start, mid);
        result = std::min(result, std::abs(andSum - target));

        if (andSum > target) {
          left = mid + 1;
        } else {
          right = mid - 1;
        }
      }
    }
    return result;
  }
};
