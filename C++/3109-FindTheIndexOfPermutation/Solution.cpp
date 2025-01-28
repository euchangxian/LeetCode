#include <cstddef>
#include <cstdlib>
#include <vector>

constexpr int MOD = 1'000'000'007;

class FenwickTree {
 public:
  // do a presence array, tree[x] = 1 means the integer x is present.
  FenwickTree(int n) : N(n), tree_(N + 1, 1) {
    for (int i = 1; i <= N; ++i) {
      if (i + (i & -i) <= N) {
        tree_[i + (i & -i)] += tree_[i];
      }
    }
  }

  void update(int i, int diff) {
    for (; i <= N; i += (i & -i)) {
      tree_[i] += diff;
    }
  }

  int query(int i) const {
    int sum = 0;
    for (; i > 0; i -= (i & -i)) {
      sum += tree_[i];
    }
    return sum;
  }

 private:
  const int N;
  std::vector<int> tree_;
};

using i64 = long long;
class Solution {
 public:
  int getPermutationIndex(std::vector<int>& perm) {
    // Find the position of perm in the sorted order of the permutations of
    // [1..n].
    //
    // WTF...
    // Naively, start with [1..N] and call std::next_permutation repeatedly.
    // O(n^2).
    // Too slow I guess, LOL.
    //
    // MAFFS.
    // if perm[0] == x, then there are at least (x-1) * (n-1)! permutations
    // before perm (all the permutations with a smaller starting number).
    // Similarly, if perm[1] == y, then there are at least (y-1) * (n-2)!
    // permutations before perm.
    //
    // Therefore, we can elucidate perm[i]:
    // if perm[i] == a, then there are at least (a-1) * (n-i-1)! permutations
    // before.
    //
    // Thus, we can count! based on the integers that are smaller than perm[i].
    const int n = perm.size();

    std::vector<i64> fact(n);
    fact[0] = 1;
    for (int i = 1; i < n; ++i) {
      fact[i] = fact[i - 1] * i % MOD;
    }

    int result = 0;
    FenwickTree ft(n);
    for (int i = 0; i < n; ++i) {
      int smaller = ft.query(perm[i] - 1);
      result = ((1LL * result) + (smaller * fact[n - i - 1])) % MOD;
      ft.update(perm[i], -1);
    }

    return result;
  }
};
