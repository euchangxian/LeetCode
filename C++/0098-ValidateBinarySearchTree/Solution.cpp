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
  // Note that previous is passed by reference
  bool inorder(TreeNode* curr, TreeNode*& prev) {
    if (!curr) {
      return true;
    }

    if (!inorder(curr->left, prev)) {
      return false;
    }

    if (prev && prev->val >= curr->val) {
      return false;
    }

    prev = curr;  // Update the prev node
    return inorder(curr->right, prev);
  }

 public:
  bool isValidBST(TreeNode* root) {
    // Traverse in-order
    TreeNode* prev = nullptr;
    return inorder(root, prev);
  }
};
