#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <unordered_map>
#include <utility>
#include <vector>

class UnionFind {
 public:
  UnionFind(int n)
      : components_(n), largest_(1), parent_(n), rank_(n, 0), size_(n, 1) {
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
      largest_ = std::max(largest_, size_[rootY]);
      return;
    }

    if (rank_[rootX] == rank_[rootY]) {
      ++rank_[rootX];
    }
    parent_[rootY] = rootX;
    size_[rootX] += std::exchange(size_[rootY], 0);
    largest_ = std::max(largest_, size_[rootX]);
  }

  int components() const noexcept { return components_; }

  int size(int x) { return size_[find(x)]; }

  int largest() const { return largest_; }

 private:
  int components_;
  int largest_;

  std::vector<int> parent_;
  std::vector<int> rank_;
  std::vector<int> size_;
};

std::vector<int> getPrimeFactors(int n) {
  std::vector<int> factors;

  // optimization
  if (n % 2 == 0) {
    factors.push_back(2);

    while (n % 2 == 0) {
      n /= 2;
    }
  }

  for (int i = 3; i * i <= n; i += 2) {
    if (n % i == 0) {
      factors.push_back(i);
    }

    while (n % i == 0) {
      n /= i;
    }
  }

  if (n > 2) {
    factors.push_back(n);
  }
  return factors;
}

class Solution {
 public:
  int largestComponentSize(std::vector<int>& nums) {
    // n nodes, labelled nums[0] to nums[n-1]
    // - Connect nums[i] to nums[j] if nums[i] and nums[j] share a common
    //   factor greater than 1.
    // Prime factorization? Then union.
    // Though, constraints n <=2*10e4 allow for O(N^2).
    const int n = nums.size();
    UnionFind G(n);

    std::unordered_map<int, int> seen;
    for (int i = 0; i < n; ++i) {
      if (nums[i] == 1) {
        continue;
      }
      for (int prime : getPrimeFactors(nums[i])) {
        auto it = seen.find(prime);
        if (it != seen.end()) {
          G.unite(it->second, i);
        } else {
          seen[prime] = i;
        }
      }
    }

    return G.largest();
  }
};
