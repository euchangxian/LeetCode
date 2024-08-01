#include "../commons/TreeNode.h"
#include <cstdlib>

class Solution {
public:
  int postOrderTraversal(TreeNode *root, int *moves) {
    if (root == nullptr) {
      return 0;
    }
    int leftExtra = postOrderTraversal(root->left, moves);
    int rightExtra = postOrderTraversal(root->right, moves);

    *moves += std::abs(leftExtra) + std::abs(rightExtra);

    return root->val + leftExtra + rightExtra - 1;
  }

  int distributeCoins(TreeNode *root) {
    int moves = 0;
    postOrderTraversal(root, &moves);
    return moves;
  }
};
