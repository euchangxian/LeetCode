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
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    // Exploit the sorted property of a BST
    // O(logn) assuming the BST is balanced
    // Question constraints guarantee that p and q exists. Therefore, there
    // must be an LCA which will never be null
    if (p->val < root->val && q->val < root->val) {
      // Both p and q lie in the left subtree
      return lowestCommonAncestor(root->left, p, q);
    }

    if (p->val > root->val && q->val > root->val) {
      // Both p and q lie in the right subtree
      return lowestCommonAncestor(root->right, p, q);
    }

    // Split found
    return root;
  }

  TreeNode* lowestCommonAncestorNaive(TreeNode* root,
                                      TreeNode* p,
                                      TreeNode* q) {
    // Does not make use of the sorted property of a BST
    // O(n)
    if (!root) {
      return nullptr;
    }

    if (root == p || root == q) {
      return root;
    }

    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);

    if (left && right) {
      // root is the LCA
      return root;
    }

    if (left) {
      // Left root is the LCA
      return left;
    }

    return right;
  }
};
