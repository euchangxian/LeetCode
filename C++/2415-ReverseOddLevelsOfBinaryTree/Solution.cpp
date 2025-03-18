#include <cstddef>
#include <cstdlib>
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
 private:
  void keepEven(TreeNode* leftChild, TreeNode* rightChild) {
    if (!leftChild || !rightChild) {
      return;
    }

    reverseOdd(leftChild->left, rightChild->right);
    reverseOdd(leftChild->right, rightChild->left);
  }

  void reverseOdd(TreeNode* leftChild, TreeNode* rightChild) {
    if (!leftChild || !rightChild) {
      return;
    }

    // NOTE we only want to swap the values, not the entire subtree.
    std::swap(leftChild->val, rightChild->val);

    keepEven(leftChild->left, rightChild->right);
    keepEven(leftChild->right, rightChild->left);
  }

  template <bool isOdd>
  void traverse(TreeNode* leftChild, TreeNode* rightChild) {
    if (!leftChild || !rightChild) {
      return;
    }

    if constexpr (isOdd) {
      std::swap(leftChild->val, rightChild->val);
    }

    traverse<!isOdd>(leftChild->left, rightChild->right);
    traverse<!isOdd>(leftChild->right, rightChild->left);
  }

 public:
  TreeNode* reverseOddLevels(TreeNode* root) {
    // Given perfect binary tree, i.e., each node has either 0 children, or 2
    // children, every leaf node is on the same level.
    //  Start at level 0.
    if (!root) {
      return nullptr;
    }

    // reverseOdd(root->left, root->right);
    traverse<true>(root->left, root->right);
    return root;
  }
};
