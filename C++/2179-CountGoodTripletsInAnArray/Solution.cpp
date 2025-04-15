#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

using i64 = long long;
constexpr int MAX_N = 1e5;

class FenwickTree {
 public:
  FenwickTree(int n) : N(n), tree(N + 1, 0) {}

  int query(int l, int r) const { return prefix(r) - prefix(l - 1); }

  int prefix(int i) const {
    int sum = 0;
    for (; i > 0; i -= i & -i) {
      sum += tree[i];
    }
    return sum;
  }

  void update(int i, int diff) {
    for (; i <= N; i += i & -i) {
      tree[i] += diff;
    }
  }

  void reset() { std::fill(tree.begin(), tree.end(), 0); }

 private:
  const int N;
  std::vector<int> tree;
};

class Solution {
 public:
  i64 goodTriplets(std::vector<int>& nums1, std::vector<int>& nums2) {
    const int n = nums1.size();

    std::vector<int> pos2(n);
    for (int i = 0; i < n; ++i) {
      pos2[nums2[i]] = i + 1;  // 1-indexed for more intuitive FT queries.
    }

    // Keyed by value.
    FenwickTree ft(n);
    i64 result = 0;

    // To optimize to 1-pass, the key insight is to iterate over nums1[j] as
    // the middle element.
    // Count the number of elements
    for (int j = 0; j < n; ++j) {
      int y = pos2[nums1[j]];

      // Query x < y in nums2
      i64 left = ft.prefix(y - 1);

      // We want z > y, while also ensuring k > j
      // Given that we have n distinct elements, we take n-y to get the number
      // of elements greater than y. This fulfils z > y
      // Then, with j-left giving us the number of elements in nums1 that are
      // already processed, and to the right of y.
      // we can do (n-y) - (j-left) to get the number of elements to the right
      // of y, that have not yet been processed, i.e., to the right of j in
      // nums1, fulfilling k > j.
      i64 right = (n - y) - (j - left);
      result += left * right;

      ft.update(y, 1);
    }
    return result;
  }

  i64 goodTripletsNaive(std::vector<int>& nums1, std::vector<int>& nums2) {
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
