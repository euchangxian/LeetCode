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
  int sumRootToLeaf(TreeNode* root) {
    // Given root. Each node is 0 or 1.
    // Each root-to-leaf path represent a binary number, starting with the MSB.
    // Return the sum of all numbers represented at the leaves.
    //
    // DFS.
    auto dfs = [](this auto&& dfs, TreeNode* node, int curr) {
      if (!node) {
        return 0;
      }

      curr = (curr << 1) | node->val;
      if (!node->left && !node->right) {
        return curr;
      }
      return dfs(node->left, curr) + dfs(node->right, curr);
    };
    return dfs(root, 0);
  }
};
