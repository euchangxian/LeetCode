#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <iterator>
#include <vector>

// Feels like Range Maximum Queries, since it seems that any element above the
// threshold frequency can be returned. Segment Tree?
// Though, there are no updates required?
// Note the name is literally Majority Element i.e., LC 169. Majority Element,
// where the algorithm is akin to taking prefix majority.
// Working it out, the Prefix Majority is an inversible operation.
// i.e., inverse(majority(nums[:i]), majority(nums[:j])) is equivalent to
// taking the majority(nums[j:i]).
// This is done by keep track of the prefix majority and its exceedance (not
// the prefix frequency, but how much more it exceeds the frequency of all
// other elements, like in the simpler variant) at index i and j.
constexpr int MAX_N = 2 * 10000;
struct Node {
  int majority{-1};
  int frequency{0};
};

class SegmentTree {
 public:
  SegmentTree(const std::vector<int>& arr) : N(arr.size()), tree{} {
    build(arr, 1, 0, N - 1);
  }

  Node query(int l, int r) const { return query_(1, 0, N - 1, l, r); }

 private:
  const int N;

  std::array<Node, 4 * (MAX_N + 1)> tree;

  static constexpr int left(int i) { return i << 1; }

  static constexpr int right(int i) { return (i << 1) + 1; }

  static constexpr Node merge(const Node& a, const Node& b) {
    if (a.majority == b.majority) {
      return {a.majority, a.frequency + b.frequency};
    }

    if (a.frequency > b.frequency) {
      return {a.majority, a.frequency - b.frequency};
    }

    return {b.majority, b.frequency - a.frequency};
  }

  void build(const std::vector<int>& arr, int idx, int L, int R) {
    if (L == R) {
      tree[idx] = {arr[L], 1};
    } else {
      int mid = (L + R) / 2;
      build(arr, left(idx), L, mid);
      build(arr, right(idx), mid + 1, R);

      tree[idx] = merge(tree[left(idx)], tree[right(idx)]);
    }
  }

  Node query_(int idx, int L, int R, int l, int r) const {
    if (l > r) {
      // WARNING: to simplify the merge function, return (0, 0) instead of
      // (-1, -1), to avoid having to check for such invalid ranges.
      // Both 0 and -1 are considered invalid given the constraints anyways.
      return {0, 0};
    }

    if (l <= L && R <= r) {
      return tree[idx];
    }

    int mid = (L + R) / 2;
    return merge(query_(left(idx), L, mid, l, std::min(mid, r)),
                 query_(right(idx), mid + 1, R, std::max(mid + 1, l), r));
  }
};

class MajorityChecker {
 public:
  MajorityChecker(std::vector<int>& arr) : st(arr) {
    for (int i = 0; i < arr.size(); ++i) {
      // tracks the indices of the occurences of the value.
      occurences[arr[i]].push_back(i);
    }
  }

  int query(int left, int right, int threshold) {
    auto [majority, excess] = st.query(left, right);
    if (majority == 0) {
      return -1;
    }

    const auto& indices = occurences[majority];

    // find the smallest index in occurences[majority] that contains the range
    // [left, right], inclusive
    int lb =
        std::distance(indices.begin(),
                      std::lower_bound(indices.begin(), indices.end(), left));
    int ub =
        std::distance(indices.begin(),
                      std::upper_bound(indices.begin(), indices.end(), right));

    // no need to +1, since ub is already +1 (unless std::prev is called)
    if (ub - lb < threshold) {
      return -1;
    }
    return majority;
  }

 private:
  SegmentTree st;
  std::array<std::vector<int>, MAX_N + 1> occurences;
};

/**
 * Your MajorityChecker object will be instantiated and called as such:
 * MajorityChecker* obj = new MajorityChecker(arr);
 * int param_1 = obj->query(left,right,threshold);
 */
