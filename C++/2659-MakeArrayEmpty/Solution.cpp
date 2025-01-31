#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <utility>
#include <vector>

class FenwickTree {
 public:
  FenwickTree(int n) : N(n), tree(N + 1, 1) {
    for (int i = 1; i <= N; ++i) {
      int parent = i + (i & -i);

      if (parent <= N) {
        tree[parent] += tree[i];
      }
    }
  }

  int query(int l, int r) const { return query_(r) - query_(l - 1); }

  int query_(int i) const {
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

 private:
  const int N;
  std::vector<int> tree;
};
using i64 = long long;
class Solution {
 public:
  i64 countOperationsToEmptyArray(std::vector<int>& nums) {
    // Seems similar to 1505-Minimum Possible Integer after at most K
    // Adjacent Swaps, where we want to "greedily" bring the smallest element
    // to the front.
    // In this case, each operation is either:
    // - remove the smallest element if it is at the front, or
    // - bring the front element to the back. Equivalent to a left shift.
    //
    // Fenwick Trees + presence array, counting the number of elements to the
    // left of the minimum.
    // However, need to keep track of the (circular) rotation.
    //
    // nums = [-4, -13, -12]
    // sorted=[{-13, 2}, {-12, 3}, {-4, 1}]
    //
    // iter1: [-12, -4], ops = 2
    // iter2: ahh, query(1, 2) will return 1, +1 for the pop, ops = 4, which is
    // overcounting. need to subtract how far this element was from the prevMin.
    const int n = nums.size();
    std::vector<std::pair<int, int>> sorted;
    sorted.reserve(n);
    for (int i = 0; i < n; ++i) {
      // keep track of original index so we can query elements to the left.
      // 1-indexed for FTs.
      sorted.emplace_back(nums[i], i + 1);
    }
    std::sort(sorted.begin(), sorted.end());

    FenwickTree ft(n);
    i64 ops = 0;
    int head = 1;  // tracks the rotation of the nums.
    for (const auto [_, idx] : sorted) {
      // swaps + pop.
      if (head <= idx) {
        ops += ft.query(head, idx - 1);
      } else {
        ops += ft.query(head, n) + ft.query(1, idx - 1);
      }

      ++ops;
      ft.update(idx, -1);
      head = idx;
    }
    return ops;
  }
};
