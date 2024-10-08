#include "../commons/TreeNode.h"

class Solution {
 public:
  bool evaluateTree(TreeNode* root) {
    if (root->left == nullptr && root->right == nullptr) {
      // leaf node
      return root->val;
    }

    if (root->val == 2) {
      return evaluateTree(root->left) || evaluateTree(root->right);
    }
    return evaluateTree(root->left) && evaluateTree(root->right);
  }
};
