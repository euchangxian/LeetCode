#include <array>
#include <numeric>
#include <utility>
#include <vector>

class UnionFind {
 public:
  UnionFind(int n) : components_(n), parent_(n), rank_(n, 0), size_(n, 1) {
    std::iota(parent_.begin(), parent_.end(), 0);
  }

  int find(int x) noexcept {
    if (parent_[x] != x) {
      parent_[x] = find(parent_[x]);
    }

    return parent_[x];
  }

  bool connected(int x, int y) noexcept { return find(x) == find(y); }

  void unite(int x, int y) noexcept {
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

  int size(int x) noexcept { return size_[find(x)]; }

 private:
  int components_;

  std::vector<int> parent_;
  std::vector<int> rank_;
  std::vector<int> size_;
};

class Solution {
 public:
  int minimumHammingDistance(std::vector<int>& source,
                             std::vector<int>& target,
                             std::vector<std::vector<int>>& allowedSwaps) {
    // Length n source, target
    // allowedSwaps[i] = [a, b] => can swap(source[a], source[b])
    // can swap any time, any order.
    // Hamming distance of the two array is the number of positions where the
    // elements are different.
    // Number of i such that source[i] != target[i].
    // Return the minimum Hamming Distance after any amount of swap operations.
    //
    // Hm.
    // For source[i] == target[i], do we ever need to swap them?
    // Yep, transitive swaps.
    // Hm. This means we can model this as a graph problem.
    // Nodes are Indices. Connect two nodes a, b if allowedSwaps[i] = [a, b].
    //
    // UnionFind.
    // After which, we need to process source[i] -> target[j] such that
    // source[i] == target[j], mapping i -> j.
    constexpr int MAX_N = 1E5;

    const auto n = static_cast<int>(source.size());
    UnionFind uf{n};

    for (const auto& edge : allowedSwaps) {
      uf.unite(edge[0], edge[1]);
    }

    std::vector<std::vector<int>> components(n);
    for (int i = 0; i < n; ++i) {
      components[uf.find(i)].push_back(i);
    }

    std::array<int, MAX_N + 1> freq{};
    auto matches = 0;
    for (int i = 0; i < n; ++i) {
      if (components[i].empty()) {
        continue;
      }

      for (auto idx : components[i]) {
        ++freq[source[idx]];
      }

      // check how many target values are in this component
      for (auto idx : components[i]) {
        if (freq[target[idx]] > 0) {
          --freq[target[idx]];
          ++matches;
        }
      }

      // reset for next component
      for (auto idx : components[i]) {
        freq[source[idx]] = 0;
      }
    }

    return n - matches;
  }
};
