#include <utility>

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
  TreeNode* bstToGst(TreeNode* root) {
    // Given the root of a BST, convert it to a Greater Tree, such that every
    // key of the original BST is changed to the original key plus the sum of
    // all keys greater than the original key.
    //
    // Hm. Seems like a right -> node -> left recursion, maintaining the sum.
    int greaterSum = 0;
    auto dfs = [&greaterSum](this auto&& dfs, TreeNode* node) {
      if (!node) {
        return;
      }
      dfs(node->right);
      node->val += std::exchange(greaterSum, greaterSum + node->val);
      dfs(node->left);
    };

    dfs(root);
    return root;
  }
};
