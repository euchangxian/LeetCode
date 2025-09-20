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

constexpr int MOD = 1'000'000'007;

// NOTE: Wrong, as of 18 March 2025.
class Solution {
 public:
  int numOfWays(std::vector<int>& nums) {
    // Observe that instead of:
    // insert root, insert left, insert right
    // we can also have the sequence root->right->left, or in a more complex
    // example:
    // root->right->right->left->left,
    // root->right->left->right->left,
    // ...,
    // Observe that there seems to be some kind of topological ordering, where
    // we can interleave two different groups, left1->left2 and right1->right2
    // Then, the number of ways would be left.size() * right.size()
    // Reduced to a traversal + DSU problem.
    // Still need a DFS I believe? Not simply 2 components where the LEFT
    // components consists of numbers smaller than the first element, and vice
    // versa.
    // This is because even within the LEFT/RIGHT component, there is a
    // topological order, recursively.
    // DP/D&C may be more suitable. Though, given the representation of the
    // nodes, not so trivial to recurse on left/right subtrees.
    // Hm. May not be so complicated. Just count LEFT/RIGHT, then do some
    // counting, i.e., slots
    // E.g., if LEFT=2, RIGHT=2, then the number of ways to arrange:
    // _L_L_
    // 3 * 2 - 1 (original)
    const int n = nums.size();
    UnionFind G(n + 2);
    const int LEFT = n;
    const int RIGHT = n + 1;

    for (int i = 1; i < nums.size(); ++i) {
      if (nums[i] < nums[0]) {
        G.unite(LEFT, i);
      } else {
        G.unite(RIGHT, i);
      }
    }

    // minus 1 for the Sentinel node itself.
    int left = G.size(LEFT) - 1;
    int right = G.size(RIGHT) - 1;
    return ((static_cast<long long>(left) + 1) * right - 1) % MOD;
  }
};
