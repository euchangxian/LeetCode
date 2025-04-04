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
  TreeNode* lcaDeepestLeaves(TreeNode* root) {
    // LCA of deepest leaves.
    // - Leaf if no children
    // - only want LCA of nodes with maximum depth.
    //
    // Naively, two passes. One to calculate depth and determine the nodes
    // to find LCA of.
    // Then, LCA of nodes.
    return postorder(root).first;
  }

 private:
  std::pair<TreeNode*, int> postorder(TreeNode* root) {
    if (!root) {
      return {nullptr, 0};  // + 0 depth
    }

    auto [lnode, ldepth] = postorder(root->left);
    auto [rnode, rdepth] = postorder(root->right);

    // Deepest leaves in left subtree.
    if (ldepth > rdepth) {
      return {lnode, ldepth + 1};
    }

    // Deepest leaves in right subtree.
    if (rdepth > ldepth) {
      return {rnode, rdepth + 1};
    }

    // same depth, return this node as LCA
    return {root, ldepth + 1};
  }
};
