#include <vector>

/**
 * @brief UnionFind (Disjoint Set) data structure
 *
 * This class implements a Union-Find data structure, also known as a Disjoint
 * Set. It provides efficient operations for maintaining disjoint sets and
 * determining if two elements belong to the same set.
 *
 * Time Complexity:
 * - Construction: O(n)
 * - Find: O(α(n)) amortized
 * - Union: O(α(n)) amortized
 * - IsConnected: O(α(n)) amortized
 *
 * where α(n) is the inverse Ackermann function, which grows extremely slowly
 * and is effectively constant (≤4) for all practical values of n.
 *
 * Space Complexity: O(n)
 */
class UnionFind {
 private:
  // parent stores the parent of each element
  std::vector<int> parent;

  // rank stores the approximate depth of each tree rooted at i
  std::vector<int> rank;

 public:
  /**
   * @brief Construct a new UnionFind object
   *
   * @param size The number of elements in the UnionFind structure
   *
   * Initially, each element is in its own set (i.e., is its own parent).
   * Time Complexity: O(n)
   * Space Complexity: O(n)
   */
  UnionFind(int size) : parent(size), rank(size, 0) {
    for (int i = 0; i < size; ++i) {
      parent[i] = i;
    }
  }

  /**
   * @brief Find the representative (root) of the set containing x
   *
   * @param x The element to find the representative for
   * @return int The representative of the set containing x
   *
   * This method uses path compression: all nodes along the path to the root
   * are made to point directly to the root. This flattens the tree structure,
   * significantly improving the efficiency of future operations.
   *
   * Time Complexity: O(α(n)) amortized
   * - Worst case (rare): O(log n)
   * - Best case: O(1) if x is the root or has been previously compressed
   */
  int find(int x) {
    if (parent[x] != x) {
      parent[x] = find(parent[x]);  // Path compression
    }
    return parent[x];
  }

  /**
   * @brief Check if two elements are in the same set
   *
   * @param x First element
   * @param y Second element
   * @return true if x and y are in the same set, false otherwise
   *
   * Time Complexity: O(α(n)) amortized (same as find)
   */
  bool isConnected(int x, int y) { return find(x) == find(y); }

  /**
   * @brief Unite the sets containing elements x and y
   *
   * @param x Element from the first set
   * @param y Element from the second set
   *
   * This method uses union by rank: the shorter tree is always attached to the
   * root of the taller tree. This ensures that the resulting tree remains
   * balanced, keeping operations efficient.
   *
   * Time Complexity: O(α(n)) amortized
   * - The actual union is O(1), but it requires two find operations
   */
  void unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX != rootY) {
      if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
      } else if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
      } else {
        parent[rootY] = rootX;
        ++rank[rootX];
      }
    }
  }
};
