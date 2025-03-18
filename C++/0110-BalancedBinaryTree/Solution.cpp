#include <algorithm>

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
  bool isBalanced(TreeNode* root) {
    int result = height(root);

    return result != -1;
  }

 private:
  int height(TreeNode* curr) {
    if (!curr) {
      return 0;
    }

    int leftHeight = height(curr->left);
    int rightHeight = height(curr->right);

    if (leftHeight == -1 || rightHeight == -1 ||
        std::abs(leftHeight - rightHeight) > 1) {
      return -1;
    }

    return std::max(leftHeight, rightHeight) + 1;
  }
};
