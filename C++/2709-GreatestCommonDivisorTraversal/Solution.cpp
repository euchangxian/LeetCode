#include <cstddef>
#include <cstdlib>
#include <unordered_map>
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
  bool canTraverseAllPairs(std::vector<int>& nums) {
    // Can traverse from i to j if gcd(nums[i], nums[j]) > 1.
    // Determine if for every pair of indices (i, j) in nums, there exists a
    // sequence of traversal from i to j.
    // Transitive Closure kind of question. UnionFind?
    // The edges are easy to model: if gcd(nums[i], nums[j]) > 1, then there
    // exists an edge.
    // But O(n^2) all-pairs check?
    // Given constraints n<=10e5, should be possible to AC without TLE?
    // Nope. Can't.
    //
    // How do we do better? Suppose k elements are in a connected component. How
    // can we avoid comparing with the existing k elements, to determine if an
    // element should belong to this component? What GCD properties can we
    // exploit?
    const int n = nums.size();
    if (n == 1) {
      return true;
    }
    UnionFind G(n);

    // {prime, i}
    // map of prime factors to indices.
    std::unordered_map<int, int> seen;
    for (int i = 0; i < n; ++i) {
      if (nums[i] == 1) {
        return false;
      }

      for (int prime : getPrimeFactors(nums[i])) {
        auto it = seen.find(prime);
        if (it == seen.end()) {
          seen[prime] = i;
        } else {
          G.unite(seen[prime], i);
        }
      }
    }

    return G.components() == 1;
  }

 private:
  std::vector<int> getPrimeFactors(int n) {
    std::vector<int> factors;
    if (n % 2 == 0) {
      factors.push_back(2);

      while (n % 2 == 0) {
        n /= 2;
      }
    }

    for (int i = 3; i * i <= n; i += 2) {
      if (n % i == 0) {
        factors.push_back(i);

        while (n % i == 0) {
          n /= i;
        }
      }
    }

    // Edge case where n is a prime number greater than 2
    if (n > 2) {
      factors.push_back(n);
    }
    return factors;
  }
};
