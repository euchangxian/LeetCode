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
  int N;
  std::vector<int> tree;
};

constexpr int OFFSET = 1e4;
class Solution {
 public:
  std::vector<int> countSmaller(std::vector<int>& nums) {
    // Fenwick Trees keyed by values + iterate right to left.
    const int n = nums.size();

    FenwickTree ft(2 * OFFSET + 1);
    std::vector<int> answer(n);
    for (int i = n - 1; i >= 0; --i) {
      answer[i] = ft.prefix(OFFSET + nums[i]);  // nums[i] is '0-indexed'
      ft.update(OFFSET + nums[i] + 1, 1);
    }
    return answer;
  }
};
