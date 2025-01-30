#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <unordered_map>
#include <vector>

class FenwickTree {
 public:
  FenwickTree(int n) : N(n), tree(N + 1, 0) {}

  int prefix(int i) const {
    int sum = 0;
    for (; i > 0; i -= (i & -i)) {
      sum += tree[i];
    }
    return sum;
  }

  void update(int i, int diff) {
    for (; i <= N; i += (i & -i)) {
      tree[i] += diff;
    }
  }

 private:
  const int N;
  std::vector<int> tree;
};
class Solution {
 public:
  std::vector<int> countSmaller(std::vector<int>& nums) {
    // Simple! Discretization + Fenwick Trees + iterate right to left.
    std::vector<int> sorted = nums;
    std::sort(sorted.begin(), sorted.end());

    int k = 1;
    std::unordered_map<int, int> indices;
    indices.reserve(nums.size());
    indices[sorted[0]] = k;
    for (int i = 1; i < sorted.size(); ++i) {
      if (sorted[i] != sorted[i - 1]) {
        indices[sorted[i]] = ++k;
      }
    }

    FenwickTree ft(indices.size());
    std::vector<int> answer(nums.size());
    for (int i = nums.size() - 1; i >= 0; --i) {
      answer[i] = ft.prefix(indices[nums[i]] - 1);
      ft.update(indices[nums[i]], 1);
    }
    return answer;
  }
};
