#include <algorithm>
#include <array>
#include <numeric>
#include <ranges>
#include <string>
#include <string_view>
#include <tuple>
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
  std::vector<std::vector<std::string>> accountsMerge(
      std::vector<std::vector<std::string>>& accounts) {
    // accounts[i] is a list of strings, where the first element,
    // accounts[i][0] is a name, and the rest are emails.
    // Merge accounts.
    // Two accounts belong to the same person if there is some common email to
    // both accounts.
    // Same names do not necessarily mean same person.
    // After merging, return the accounts in the same format:
    // name, emails in sorted order.
    //
    // Think of each accounts[i] as a node.
    // A node i is connected to another node j if any-of accounts[i][1..k1] is
    // equal to accounts[j][1..k2]
    const auto n = static_cast<int>(accounts.size());
    UnionFind uf{n};

    std::unordered_map<std::string_view, int> emailOwner;
    for (int i = 0; i < n; ++i) {
      for (std::string_view email :
           std::span{accounts[i].begin() + 1, accounts[i].end()}) {
        if (auto it = emailOwner.find(email); it != emailOwner.end()) {
          uf.unite(it->second, i);
        } else {
          emailOwner.emplace(email, i);
        }
      }
    }

    std::unordered_map<int, std::vector<std::string_view>> byComponents;
    for (const auto [email, ownerIdx] : emailOwner) {
      byComponents[uf.find(ownerIdx)].emplace_back(email);
    }

    std::vector<std::vector<std::string>> result;
    result.reserve(uf.components());
    for (auto [ownerIdx, emails] : byComponents) {
      std::ranges::sort(emails);

      std::vector<std::string> collated;
      collated.reserve(1 + emails.size());
      collated.emplace_back(std::move(accounts[ownerIdx][0]));

      for (auto email : emails) {
        collated.emplace_back(email);
      }
      result.emplace_back(std::move(collated));
    }

    return result;
  }
};
