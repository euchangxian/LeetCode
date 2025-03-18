#include <cstdlib>

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
  int postOrderTraversal(TreeNode* root, int* moves) {
    if (root == nullptr) {
      return 0;
    }
    int leftExtra = postOrderTraversal(root->left, moves);
    int rightExtra = postOrderTraversal(root->right, moves);

    *moves += std::abs(leftExtra) + std::abs(rightExtra);

    return root->val + leftExtra + rightExtra - 1;
  }

  int distributeCoins(TreeNode* root) {
    int moves = 0;
    postOrderTraversal(root, &moves);
    return moves;
  }
};
