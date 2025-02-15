#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iterator>
#include <ranges>
#include <utility>
#include <vector>
using i64 = long long;

class UnionFind {
 public:
  UnionFind(int n, std::vector<int>& nums)
      : parent_(n), rank_(n, 0), sum_(n, 0LL) {
    for (int i = 0; i < n; ++i) {
      parent_[i] = i;

      if (nums[i] > 0) {
        sum_[i] = nums[i];
      }
    }
  }

  void track(int x, int val) {
    sum_[x] = val;
    maxSum_ = std::max(maxSum_, sum_[x]);
  }

  int find(int x) {
    if (parent_[x] != x) {
      parent_[x] = find(parent_[x]);
    }

    return parent_[x];
  }

  bool connected(int x, int y) { return find(x) == find(y); }

  void unite(std::vector<int>& nums, int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY) {
      return;
    }

    if (rank_[rootX] < rank_[rootY]) {
      parent_[rootX] = rootY;
      sum_[rootY] += std::exchange(sum_[rootX], 0LL);

      maxSum_ = std::max(maxSum_, sum_[rootY]);
      return;
    }

    if (rank_[rootX] == rank_[rootY]) {
      ++rank_[rootX];
    }
    parent_[rootY] = rootX;
    sum_[rootX] += std::exchange(sum_[rootY], 0LL);
    maxSum_ = std::max(maxSum_, sum_[rootX]);
  }

  int sum(int x) { return sum_[find(x)]; }

  i64 maxSum() { return maxSum_; }

 private:
  i64 maxSum_{0};

  std::vector<int> parent_;
  std::vector<int> rank_;
  std::vector<i64> sum_;
};

class Solution {
 public:
  std::vector<i64> maximumSegmentSum(std::vector<int>& nums,
                                     std::vector<int>& removeQueries) {
    // Reverse approach.
    // Augmented UnionFind, adjacent numbers in same component if they are
    // not removed.
    // Iteratively add removed numbers.
    const int n = nums.size();
    for (int i : removeQueries) {
      nums[i] = -nums[i];  // negative to indicate removed.
    }

    UnionFind G(n, nums);
    if (nums[0] > 0) {
      G.track(0, nums[0]);
    }

    for (int i = 1; i < n; ++i) {
      if (nums[i] > 0) {
        G.track(i, nums[i]);
      }

      if (nums[i] >= 0 && nums[i - 1] >= 0) {
        G.unite(nums, i - 1, i);
      }
    }

    std::vector<i64> answer(removeQueries.size());
    auto it = answer.rbegin();
    for (int i : removeQueries | std::ranges::views::reverse) {
      *it = G.maxSum();
      ++it;

      nums[i] = -nums[i];
      G.track(i, nums[i]);

      if (i > 0 && nums[i - 1] >= 0) {
        G.unite(nums, i, i - 1);
      }

      if (i < n - 1 && nums[i + 1] >= 0) {
        G.unite(nums, i, i + 1);
      }
    }
    return answer;
  }
};
