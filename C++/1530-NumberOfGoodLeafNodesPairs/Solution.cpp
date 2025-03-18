#include <vector>

#ifdef LOCAL
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;

  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};
#endif  // LOCAL

constexpr int MAX_DISTANCE = 10;

class Solution {
 public:
  int countPairs(TreeNode* root, int distance) {
    // The shortest path between two different nodes in a Tree is simply
    // the shortest path from their Lowest Common Ancestor
    // DFS to any node in the tree will traverse the shortest path
    int result = 0;
    dfs(root, distance, result);
    return result;
  }

 private:
  // Returns the number of leaf nodes d distance away
  // 1 <= distance <= 10
  std::vector<int> dfs(TreeNode* node, int distance, int& result) {
    if (node == nullptr) {
      return std::vector<int>(MAX_DISTANCE + 1, 0);
    }

    if (node->left == nullptr && node->right == nullptr) {
      std::vector<int> nodesAtDistance(MAX_DISTANCE + 1, 0);
      nodesAtDistance[0] = 1;
      return nodesAtDistance;
    }

    std::vector<int> leftNodesAtDistance = dfs(node->left, distance, result);
    std::vector<int> rightNodesAtDistance = dfs(node->right, distance, result);

    // Iterate over all pairs of distances to find good pairs
    for (int i = 0; i <= distance; ++i) {
      for (int j = 0; j <= distance; ++j) {
        if ((i + 1) + (j + 1) <= distance) {
          result += leftNodesAtDistance[i] * rightNodesAtDistance[j];
        }
      }
    }

    // Update nodesAtDistance to be returned up the call stack
    std::vector<int> nodesAtDistance(MAX_DISTANCE + 1, 0);
    for (int i = 0; i < MAX_DISTANCE; ++i) {
      // Increment the distance of each node in the left and right subtree,
      // combine them into the current nodesAtDistance std::vector.
      // Similar to "right-shifting" every element
      nodesAtDistance[i + 1] = leftNodesAtDistance[i] + rightNodesAtDistance[i];
    }

    return nodesAtDistance;  // intermediate nodes return 0
  }
};
