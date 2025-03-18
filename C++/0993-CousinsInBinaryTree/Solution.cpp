#include <cstddef>
#include <queue>

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
  bool isCousins(TreeNode* root, int x, int y) {
    // Nodes have distinct values. x != y
    // Level order traversal
    std::queue<TreeNode*> frontier;
    frontier.push(root);

    while (!frontier.empty()) {
      int n = frontier.size();

      // Only consider same depth.
      TreeNode* parentX = nullptr;
      TreeNode* parentY = nullptr;

      while (n--) {
        TreeNode* parent = frontier.front();
        frontier.pop();

        if (parent->left) {
          if (parent->left->val == x) {
            parentX = parent;
          }
          if (parent->left->val == y) {
            parentY = parent;
          }

          frontier.push(parent->left);
        }

        if (parent->right) {
          if (parent->right->val == x) {
            parentX = parent;
          }

          if (parent->right->val == y) {
            parentY = parent;
          }
          frontier.push(parent->right);
        }
      }

      if (parentX && parentY) {
        return parentX != parentY;  // cousins have different parents
      }
    }
    return false;  // should not reach here for valid inputs.
  }
};
