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
  int countComponents(std::vector<int>& nums, int threshold) {
    // Two nodes (i, j) are connected by an undirected edge iff
    // lcm(nums[i], nums[j]) <= threshold.
    // Want: Number of connected components.
    // Hm. Naive O(N^2) std::lcm on all pairs will probably TLE.
    //
    // First observation: We only need to consider nums[i] <= threshold.
    // Everthing else will be in its own connected component ALONE.
    //
    // Consider: gcd(a, b) * lcm(a, b) = a * b.
    // GCD takes the minimum of the exponents, while LCM takes the maximum.
    // Thus, min(x, y) + max(x, y) = x + y (rest of the proof is trivial)
    //
    // What properties of LCM can we use to avoid checking all pairs?
    // Given two numbers a, b, we can get their prime factors:
    // a = 2^i * 3^j * ...
    // b = 2^x * 3^y * ...
    // Then, we can represent lcm(a, b) = 2^max(i, x) * 3^max(j, y) * ...
    // Hm. Then, when considering a new number c, we want to avoid having to
    // compare against BOTH a and b.
    //
    // Primes doesnt seem feasible, since LCM seem to require checking
    // ALL prime factors, while the GCD variants require only checking a single
    // prime factor.
    //
    // Contrast to 1627. Graph Connectivity with Threshold, where nodes are
    // connected if they share a common divisor greater than the specified
    // threshold (need consider composite factors too. Not just primes).
    // What if we were to initialize a DSU containing nodes from [1..threshold]?
    // Then we can connect a number to all its multiples.
    //
    // But how to deal with multiples that do not occur in nums?
    const int n = nums.size();
    UnionFind G(threshold + 1);
    std::vector<bool> seen(threshold + 1, false);

    int outsideDSU = 0;
    int inDSU = 0;
    for (int num : nums) {
      if (num > threshold) {
        ++outsideDSU;
        continue;
      }

      for (int i = num; i <= threshold; i += num) {
        if (!seen[i]) {
          seen[i] = true;
          ++inDSU;
        }
        G.unite(num, i);
      }
    }

    // Derive the actual number of connected components
    // threshold+1 - inDSU gives us the number of connected components that
    // should not be considered in our calculations, since they are not formed
    // from multiples of any nums[i].
    int components = G.components() - (threshold + 1 - inDSU);

    return outsideDSU + components;
  }
};
