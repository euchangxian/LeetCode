#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

using i64 = long long;
class FenwickTree {
 public:
  FenwickTree(int n) : N(n), tree(N + 1, 0) {}

  int query(int l, int r) const { return query_(r) - query_(l - 1); }

  void update(int i, int diff) {
    for (; i <= N; i += i & -i) {
      tree[i] += diff;
    }
  }

  void reset() { std::fill(tree.begin(), tree.end(), 0); }

 private:
  const int N;
  std::vector<int> tree;

  int query_(int i) const {
    int sum = 0;
    for (; i > 0; i -= i & -i) {
      sum += tree[i];
    }
    return sum;
  }
};

class Solution {
 public:
  i64 goodTriplets(std::vector<int>& nums1, std::vector<int>& nums2) {
    // both nums1 and nums2 are permutations of [0..n-1].
    // A good triplet is a set of 3 distinct values present in both
    // nums1 and nums2.
    // i.e., if we consider the set of values (a, b, c), which corresponds to
    // the indices (i, j, k) in nums1, and (x, y, z) in nums2, then:
    // - i < j < k, and
    // - x < y < z.
    // Ordered by position.
    //
    // Seems like Presence Arrays + Fenwick Trees + iteration order.
    // Fix b in nums1, query if (a, c) are present in nums2, and vice versa?
    // Something like leftCount[i] * rightCount[i].
    // Require mapping nums1 values to nums2 indices and vice-versa?
    //
    // Seems like one pass is sufficient.
    //
    // left2 = [0, 1, 1, 3, 3]
    // right2= [4, 2, 2, 0, 0]
    const int n = nums1.size();
    std::vector<int> mapping(n);
    for (int i = 0; i < n; ++i) {
      mapping[nums2[i]] = i + 1;  // 1-indexed.
    }

    std::vector<int> leftCount(n, 0);
    FenwickTree ft(n);
    for (int i = 0; i < n; ++i) {
      // prefix queries.
      leftCount[i] = ft.query(1, mapping[nums1[i]] - 1);
      ft.update(mapping[nums1[i]], 1);
    }

    ft.reset();
    std::vector<int> rightCount(n, 0);
    for (int i = n - 1; i >= 0; --i) {
      rightCount[i] = ft.query(mapping[nums1[i]] + 1, n);
      ft.update(mapping[nums1[i]], 1);
    }

    i64 answer = 0;
    for (int i = 1; i < n - 1; ++i) {
      answer += 1LL * leftCount[i] * rightCount[i];
    }
    return answer;
  }
};
