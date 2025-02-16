#include <bitset>
#include <cstddef>
#include <cstdlib>
#include <vector>

constexpr int MAX_N = 20;
class Solution {
 public:
  std::vector<int> constructDistancedSequence(int n) {
    // find a sequence such that:
    // - 1 is in the sequence
    // - every integer in [2..n] occurs twice
    // - for every integer i in [2..n], their occurences are i distance apart.
    //   i.e., 2x2, where i = 0, j = 2, distance = |j-i| = 2
    // Return lexicographically largest. There is always a solution.
    // The result is always (n-1)*2 + 1 length
    //
    // Given small constraints of n <= 20, we can just backtrack.
    // Greedily try to place the largest available number and DFS, pruning
    // appropriately.
    //
    // Settle largest number first? Seems palindromic like.
    // Greedy approach may not necessarily work, will require backtracking logic
    // to satisfy constraints.
    // E.g., n=3, sequence = [3, 1, 2, 3, 2]
    // A naive greedy one would attempt to place 3, 2, 1 and fail to place the
    // next number, as it requires both 2 and 3.
    // Or rather, the sequence have to be zig-zagging of some sorts?
    // Let m = n-1, then:
    // [n, m, ...] where the next position of n have to be placed at index n,
    // while the next position of m have to be placed at (1+m) = n, conflicting.
    //
    // Again, with n=5, this alternating strategy n, n-2, n-1, will not work
    // naively.
    // 5, 3, 4, 2, 3, _
    // Third position can not be 3+1, i.e., n-1
    // Lets just do naive.
    // Try to assign integers x at index i and i+x
    // Back track if not possible
    std::bitset<MAX_N + 1> used{};

    std::vector<int> result(2 * (n - 1) + 1, 0);
    dfs(used, result, n, 0);
    return result;
  }

 private:
  bool dfs(std::bitset<MAX_N + 1>& used,
           std::vector<int>& result,
           const int n,
           int idx) {
    if (idx >= result.size()) {
      return true;
    }

    // already have a number!
    if (result[idx]) {
      return dfs(used, result, n, idx + 1);
    }

    for (int i = n; i >= 1; --i) {
      if (used[i]) {
        continue;
      }

      // try
      used[i] = true;
      result[idx] = i;
      if (i == 1) {
        if (dfs(used, result, n, idx + 1)) {
          return true;
        }
      } else if (idx + i < result.size() && result[idx + i] == 0) {
        result[idx + i] = i;

        if (dfs(used, result, n, idx + 1)) {
          return true;
        }

        result[idx + i] = 0;
      }

      used[i] = false;
      result[idx] = 0;
    }

    return false;
  }
};
