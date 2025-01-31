#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <ranges>
#include <unordered_map>
#include <vector>

class FenwickTree {
 public:
  FenwickTree(int n) : N(n), tree(N + 1, 0) {}

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
  int createSortedArray(std::vector<int>& instructions) {
    // Given array of instructions, instructions[i] = ith element to be
    // inserted into nums.
    // The cost of each insertion is the minimum of:
    // - number of elements in nums that are strictly less than instr[i]
    // - number of elements in nums that are strictly greater than instr[i]
    //
    // Discretization + Fenwick trees.
    std::vector<int> sorted = instructions;
    std::sort(sorted.begin(), sorted.end());
    int k = 1;
    std::unordered_map<int, int> rank;
    rank.reserve(sorted.size());
    rank[sorted[0]] = k;
    for (int i = 1; i < sorted.size(); ++i) {
      if (sorted[i] != sorted[i - 1]) {
        rank[sorted[i]] = ++k;
      }
    }

    constexpr int MOD = 1000000007;
    const int maxRank = rank[sorted.back()];

    FenwickTree ft(rank.size());
    int cost = 0;
    for (int idx :
         instructions | std::ranges::views::transform(
                            [&rank](int num) -> int { return rank[num]; })) {
      int less = ft.query(1, idx - 1);
      int greater = ft.query(idx + 1, maxRank);

      cost = (1LL * cost + std::min(less, greater)) % MOD;
      ft.update(idx, 1);
    }
    return cost;
  }
};
