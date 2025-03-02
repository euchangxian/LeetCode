#include <cstddef>
#include <cstdlib>
#include <utility>
#include <vector>

class UnionFind {
 public:
  UnionFind(int n) : components_(n), parent_(n), rank_(n, 0), size_(n, 1) {
    for (int i = 0; i < n; ++i) {
      parent_[i] = i;
    }
  }

  int find(int x) {
    if (parent_[x] != x) {
      parent_[x] = find(parent_[x]);
    }

    return parent_[x];
  }

  bool connected(int x, int y) { return find(x) == find(y); }

  void unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY) {
      return;
    }

    --components_;
    if (rank_[rootX] < rank_[rootY]) {
      parent_[rootX] = rootY;
      size_[rootY] += std::exchange(size_[rootX], 0);
      return;
    }

    if (rank_[rootX] == rank_[rootY]) {
      ++rank_[rootX];
    }
    parent_[rootY] = rootX;
    size_[rootX] += std::exchange(size_[rootY], 0);
  }

  int components() const noexcept { return components_; }

  int size(int x) { return size_[find(x)]; }

 private:
  int components_;

  std::vector<int> parent_;
  std::vector<int> rank_;
  std::vector<int> size_;
};

class Solution {
 public:
  std::vector<bool> areConnected(int n,
                                 int threshold,
                                 std::vector<std::vector<int>>& queries) {
    // n cities labelled [1..n].
    // x and y are connected by a bidirectional road iff x and y have a common
    // divisor greater than the threshold.
    // answers[i] = true if query[i] = [u, v] is such that u and v are
    // connected.
    //
    // Get prime factors? Just a variant of some other UF question.
    // Nope. This fails to consider composite factors.
    // E.g., consider city 6 and 12, threshold = 5
    // Then, both 2*3 will be ruled out as factors, incorrectly determining
    // 6 and 12 as not connected. But 6 is a possible factor.
    UnionFind G(n + 1);
    std::vector<bool> seen(n + 1, false);
    for (int i = threshold + 1; i <= n; ++i) {
      if (seen[i]) {
        continue;
      }
      seen[i] = true;

      // for each multiple of i
      for (int multiple = i * 2; multiple <= n; multiple += i) {
        G.unite(i, multiple);
        seen[multiple] = true;
      }
    }

    std::vector<bool> answer;
    answer.reserve(queries.size());
    for (const auto& query : queries) {
      answer.push_back(G.connected(query[0], query[1]));
    }
    return answer;
  }
};
