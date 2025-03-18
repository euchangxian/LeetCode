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
  int diameterOfBinaryTree(TreeNode* root) {
    int result = 0;
    diameter(root, result);
    return result;
  }

 private:
  int diameter(TreeNode* curr, int& result) {
    if (!curr) {
      return 0;
    }

    int left = diameter(curr->left, result);
    int right = diameter(curr->right, result);

    result = std::max(result, left + right);
    return 1 + std::max(left, right);
  }
};
