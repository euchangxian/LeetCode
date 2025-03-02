#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <numeric>
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

  if (n > 2) {
    factors.push_back(n);
  }
  return factors;
}

class Solution {
 public:
  bool gcdSort(std::vector<int>& nums) {
    // Perform any number of times:
    // - swap nums[i] and nums[j] if gcd(nums[i], nums[j]) > 1
    // Return true if its possible to sort nums in non-descending order.
    //
    // Essentially, connected components. Elements within a component can be
    // swapped freely with each other (i.e., non-descending subsequence)
    //
    // The tricky part is thus determining if the different connected components
    // can create a sorted array.
    // Sort the original array (copy). Should then be possible to tell if the
    // smallest number can be swapped to that position.
    //
    // Okay, the problem is transitive closure.
    const int n = nums.size();
    UnionFind G(n);
    std::unordered_map<int, int> seen;
    for (int i = 0; i < nums.size(); ++i) {
      for (int prime : getPrimeFactors(nums[i])) {
        auto it = seen.find(prime);
        if (it != seen.end()) {
          G.unite(it->second, i);
        } else {
          seen[prime] = i;
        }
      }
    }

    std::vector<int> indices(n);
    std::iota(indices.begin(), indices.end(), 0);
    std::sort(indices.begin(), indices.end(),
              [&nums](const int i, const int j) -> bool {
                return nums[i] < nums[j] || (nums[i] == nums[j] && i < j);
              });
    for (int i = 0; i < n; ++i) {
      if (!G.connected(i, indices[i])) {
        return false;
      }
    }
    return true;
  }
};
