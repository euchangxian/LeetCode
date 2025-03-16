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
  int kthSmallest(TreeNode* root, int k) {
    // inorder traversal left->root->right, maintain global pos reference.
    int pos = 0;
    return inorder(root, k, pos);
  }

 private:
  int inorder(TreeNode* root, int k, int& pos) {
    if (root->left) {
      if (int ans = inorder(root->left, k, pos); ans != -1) {
        return ans;
      }
    }

    if (++pos == k) {
      return root->val;
    }

    if (root->right) {
      if (int ans = inorder(root->right, k, pos); ans != -1) {
        return ans;
      }
    }

    return -1;
  }
};
