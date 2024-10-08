#include <unordered_map>
#include <vector>

using namespace std;
class UnionFind {
 private:
  unordered_map<int, int> root;

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
};

class Solution {
 public:
  int minIncrementForUnique(vector<int>& nums) {
    UnionFind root;
    int moves = 0;
    for (int num : nums) {
      moves += root.find(num) - num;
    }
    return moves;
  }
};
