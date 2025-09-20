#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdint>
#include <deque>
#include <functional>
#include <iostream>
#include <istream>
#include <iterator>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using i64 = long long;

class SegmentTree {
  using Node = std::pair<int, int>;

 public:
  SegmentTree(int n) : N(n), tree(4 * N), lazy1(4 * N, -1), lazy2(4 * N, -1) {}

  SegmentTree(const std::vector<int>& nums1, const std::vector<int>& nums2)
      : SegmentTree(nums1.size()) {
    build(nums1, nums2, 0, N - 1);
  }

  void build(const std::vector<int>& nums1,
             const std::vector<int>& nums2,
             int L,
             int R) {}

  i64 query(int l, int r) { return query_(1, 0, N - 1, l, r); }

  void flip(int l, int r) { return }

 private:
  int N;

  std::vector<Node> tree;
  std::vector<int> lazy1;
  std::vector<int> lazy2;

  i64 query_(int idx, int L, int R, int l, int r) {}
};

class Solution {
 public:
  std::vector<i64> handleQuery(std::vector<int>& nums1,
                               std::vector<int>& nums2,
                               std::vector<std::vector<int>>& queries) {
    // Three type of queries:
    // 1: flip nums1[l..r] from 0 to 1, and 1 to 0.
    // 2. add nums1[i]*p to nums2[i].
    // 3. Sum of all elements in nums2.
    //
    // Intuitively, lazy-update Segment Trees, where each node store a pair
    // of values, corresponding to nums1 and nums2.
    // Expose two update methods:
    // - flipRange (which uses XOR on nums1) and
    // - updateAll to do nums2[i] += nums1[i] * p
  }
};
