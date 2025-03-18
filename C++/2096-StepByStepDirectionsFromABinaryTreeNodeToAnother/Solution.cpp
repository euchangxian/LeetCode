#include <string>

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

class Solution {
 public:
  // From their Lowest Common Ancestor:
  // shortest path from start to dest = shortest path to start + shortest path
  // to dest.
  //
  // Not a Binary Search Tree => DFS/BFS to find both.
  std::string getDirections(TreeNode* root, int startValue, int destValue) {
    std::string directionToStart;
    dfs(root, startValue, directionToStart);

    std::string directionToDest;
    dfs(root, destValue, directionToDest);

    // Find LowestCommonAncestor by matching prefix.
    int lca = 0;
    while (directionToStart[lca] == directionToDest[lca]) {
      ++lca;
    }

    std::string directions =
        std::string(directionToStart.length() - lca, 'U') +
        directionToDest.substr(lca, directionToDest.length() - lca);
    return directions;
  }

 private:
  bool dfs(TreeNode* current, int target, std::string& directions) {
    if (current == nullptr) {
      return false;
    }
    if (current->val == target) {
      return true;
    }

    directions += "L";
    bool isFound = dfs(current->left, target, directions);
    if (isFound) {
      return true;
    }
    directions.pop_back();

    directions += "R";
    isFound = dfs(current->right, target, directions);
    if (isFound) {
      return true;
    }
    directions.pop_back();
    return false;
  }
};
