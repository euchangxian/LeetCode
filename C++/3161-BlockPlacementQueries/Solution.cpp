#include <algorithm>
#include <vector>

class FenwickTree {
 public:
  FenwickTree(int n) : N(n), tree(N + 1, 0) {}

  int query(int l, int r) const { return query_(r) - query_(l - 1); }

  void update(int i, int diff) {
    for (; i <= N; i += i & -i) {
      tree[i] += diff;
    }
  }

  int query_(int i) const {
    int sum = 0;
    for (; i > 0; i -= i & -i) {
      sum += tree[i];
    }
    return sum;
  }

 private:
  const int N;
  std::vector<int> tree;
};

class Solution {
 public:
  std::vector<bool> getResults(std::vector<std::vector<int>>& queries) {
    FenwickTree ft(std::min(5 * 10000, 3 * static_cast<int>(queries.size())) +
                   1);

    for (const auto& query : queries) {
      int type = query[0];
      if (type == 1) {
        int x = query[1];
        ft.update(x + 1, 1);
      } else {
        // check if possible to place block of size sz in the range [0..x]
        // not trivial if x >> sz.
        int x = query[1];
        int sz = query[2];
      }
    }
  }
};
