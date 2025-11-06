#include <functional>
#include <numeric>
#include <queue>
#include <unordered_map>
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
  std::vector<int> processQueries(int c,
                                  std::vector<std::vector<int>>& connections,
                                  std::vector<std::vector<int>>& queries) {
    // c power stations numbered 1 to c, interconnected via n bidirectional
    // cables.
    // connections[i] = [u, v] => connection between u and v.
    // Stations in a component form a power grid.
    // All stations are initially online.
    // queries[i] = [1, x] => maintenance check for station x. if x is online,
    //                        it resolves by itself. else, the smallest id in
    //                        the same power grid resolves the check.
    //                        otherwise, -1.
    //           or [2, x] => station x goes offline.
    // Return the results of each query [1, x] in order.
    //
    // At first glance, UnionFind.
    // But notice that the components are static; they can go offline,
    // but not disconnected.
    // We need to keep track of the smallest ID per component, and each
    // station's online/offline state.
    // Naively, two ordered sets in each component?
    // UF to get the components, then 2 ordered sets to maintain lowest id.
    UnionFind uf(c);
    for (const auto& connection : connections) {
      // to 0-index
      uf.unite(connection[0] - 1, connection[1] - 1);
    }

    std::vector<bool> online(c, true);
    using MinHeap = std::priority_queue<int, std::vector<int>, std::greater<>>;
    std::unordered_map<int, MinHeap> componentQ;
    for (int station = 0; station < c; ++station) {
      auto root = uf.find(station);
      componentQ[root].emplace(station);
    }

    std::vector<int> result;
    result.reserve(queries.size());
    for (const auto& query : queries) {
      auto type = query[0];
      auto station = query[1] - 1;
      if (type == 2) {
        online[station] = false;
        continue;
      }

      if (online[station]) {
        // back to 1-index
        result.emplace_back(station + 1);
      } else {
        auto root = uf.find(station);
        auto& component = componentQ[root];

        while (!component.empty() && !online[component.top()]) {
          component.pop();
        }

        if (!component.empty()) {
          // 1-index
          result.emplace_back(component.top() + 1);
        } else {
          result.emplace_back(-1);
        }
      }
    }
    return result;
  }
};
