#include <algorithm>
#include <unordered_map>
#include <utility>
#include <vector>

using i64 = long long;

class SegmentTree {
 public:
  SegmentTree(int n) : N(n), tree(4 * N, 0) {}

  i64 query(int l, int r) { return query_(1, 0, N - 1, l, r); }

  void update(int i, i64 val) { update_(1, 0, N - 1, i, val); }

 private:
  int N;
  std::vector<i64> tree;

  static constexpr int left(int i) { return i << 1; }
  static constexpr int right(int i) { return (i << 1) + 1; }
  static constexpr i64 merge(i64 l, i64 r) { return std::max(l, r); }

  i64 query_(int idx, int L, int R, int l, int r) const {
    if (l > r) {
      return LLONG_MIN;
    }

    if (l <= L && R <= r) {
      return tree[idx];
    }

    int mid = (L + R) / 2;
    return merge(query_(left(idx), L, mid, l, std::min(r, mid)),
                 query_(right(idx), mid + 1, R, std::max(l, mid + 1), r));
  }

  void update_(int idx, int L, int R, int pos, i64 val) {
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
    tree[idx] = merge(tree[left(idx)], tree[right(idx)]);
  }
};

class Solution {
 public:
  i64 maxBalancedSubsequenceSum(std::vector<int>& nums) {
    // a length k subsequence of k indices is balanced if
    // for every j < i in the subsequence of k indices:
    // - num[i] - nums[j] >= i - j,
    //
    // Return the maximum possible sum of elements in a balanced subsequence.
    // Note that there can be negatives.
    //
    // There are multiple problems here:
    // - Determining a subsequence is balanced/finding balanced subsequence.
    // - Determining the sum of a balanced subsequence.
    //
    // Rewriting num[i] - nums[j] >= i - j:
    // - nums[i] - i >= nums[j] - j
    // which is simpler to work with.
    // Observe that by remapping nums[i] to nums[i]-i, we effectively want to
    // look for non-decreasing subsequences (not necessarily longer, since
    // nums[i] may be negative)
    //
    // Thus, finding balanced subsequence is solved.
    // Now, finding the sum (and thus the maximum sum).
    // At first glance, seems like RMQs indexed by value would suffice.
    // But on second thought, is there a need to consider negative values?
    // i.e., given that adding a negative value to the Range DS would always
    // decrease the possible maximum, WHILE simultaneously not possibly
    // excluding future, optimal values, do we have to use RMQs?
    // Fenwick Trees would suffice.
    //
    // Implementation details: Discretization is necessary.
    // NOTE: Not easy/correct with Fenwick Trees.
    // RMQs are still more suitable, to respect the left-to-right subsequence.
    const int n = nums.size();

    // {nums[i]-i, nums[i]}
    std::vector<int> sorted;
    sorted.reserve(n);

    std::vector<std::pair<int, int>> arr;
    arr.reserve(n);
    for (int i = 0; i < n; ++i) {
      arr.emplace_back(nums[i] - i, nums[i]);

      if (nums[i] > 0) {
        sorted.emplace_back(nums[i] - i);
      }
    }

    if (sorted.empty()) {
      return *std::max_element(nums.begin(), nums.end());
    }

    std::sort(sorted.begin(), sorted.end());
    int k = 0;
    std::unordered_map<int, int> rank;
    rank.reserve(sorted.size());
    rank[sorted[0]] = k;
    for (int i = 1; i < sorted.size(); ++i) {
      if (sorted[i] != sorted[i - 1]) {
        rank[sorted[i]] = ++k;
      }
    }

    i64 ans = LLONG_MIN;
    SegmentTree st(rank.size());
    for (const auto [minusI, num] : arr) {
      if (num <= 0) {
        // only update the ans, no need for insertion.
        ans = std::max(ans, static_cast<i64>(num));
      } else {
        // only query if greater than 0.
        int idx = rank[minusI];

        i64 sum = st.query(0, idx) + num;
        st.update(idx, sum);
        ans = std::max(ans, sum);
      }
    }
    return ans;
  }
};
