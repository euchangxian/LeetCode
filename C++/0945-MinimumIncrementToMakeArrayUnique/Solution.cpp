#include <unordered_map>
#include <vector>

class UnionFind {
 public:
  UnionFind() : root() {}

  int find(int x) {
    if (!root.count(x)) {
      root[x] = x;
      return x;
    }

    int nextAvailable = find(root[x] + 1);
    root[x] = nextAvailable;  // Path compression
    return nextAvailable;
  }

 private:
  std::unordered_map<int, int> root;
};

class Solution {
 public:
  int minIncrementForUnique(std::vector<int>& nums) {
    UnionFind root;
    int moves = 0;
    for (int num : nums) {
      moves += root.find(num) - num;
    }
    return moves;
  }
};
