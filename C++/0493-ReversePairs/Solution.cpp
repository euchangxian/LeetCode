#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <map>
#include <ranges>
#include <unordered_map>
#include <utility>
#include <vector>
using i64 = long long;

class FenwickTree {
 public:
  FenwickTree(const int n) : N(n), tree(N + 1, 0) {}

  int query(int l, int r) const { return query_(r) - query_(l - 1); }

  void update(int i, int diff) {
    for (; i <= N; i += (i & -i)) {
      tree[i] += diff;
    }
  }

 private:
  const int N;
  std::vector<int> tree;

  int query_(int i) const {
    int sum = 0;
    for (; i > 0; i -= (i & -i)) {
      sum += tree[i];
    }
    return sum;
  }
};

class Solution {
 public:
  int reversePairs(std::vector<int>& nums) {
    // Given integer array nums, return the number of reverse pairs in the
    // array.
    // A reverse pair is a pair (i, j) where:
    // - 0 <= i < j < nums.length (i.e., i, j are distinct indices), and
    // - nums[i] > 2 * nums[j].
    //
    // Very similar to CS3233's count decreasing triplets.
    // Discretize the values in nums, then use a Fenwick/Segment Tree to
    // query the number of values on the right that are smaller than nums[i]/2,
    // when iterating right to left.
    // Iterating left-to-right is simpler; find
    // nums[i] such that nums[j] * 2 < nums[i].
    //
    // A PURQ Fenwick Tree is sufficient.
    const int n = nums.size();

    // Create array of doubled values, then discretize both original and doubled
    // values together. This lets us map the "nums[i] > 2*nums[j]" check to
    // direct rank comparisons, without dealing with floor divisions.
    std::vector<i64> sorted;
    sorted.reserve(2 * n);
    std::vector<i64> doubled;
    doubled.reserve(n);
    for (int i = 0; i < n; ++i) {
      sorted.push_back(nums[i]);
      sorted.push_back(nums[i] * 2LL);

      doubled.push_back(nums[i] * 2LL);
    }

    std::sort(sorted.begin(), sorted.end());
    int k = 1;  // 1-indexed
    std::unordered_map<i64, int> indices;
    indices[sorted[0]] = k;
    for (int i = 1; i < sorted.size(); ++i) {
      if (sorted[i] != sorted[i - 1]) {
        indices[sorted[i]] = ++k;
      }
    }

    FenwickTree ft(indices.size());
    int answer = 0;
    // NOTE: we are iterating through the doubled values here.
    for (i64 num : doubled | std::ranges::views::reverse) {
      int count = ft.query(1, indices[num / 2] - 1);
      answer += count;
      ft.update(indices[num], 1);
    }
    return answer;
  }
};
