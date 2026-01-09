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
  TreeNode* subtreeWithAllDeepest(TreeNode* root) {
    // The depth of each node is the shortest distance to the root.
    // Return the smallest subtree such that it contains all the deepest nodes
    // in the original tree.
    //
    // Feels like Lowest Common Ancestor of all the deepest nodes.
    // A multi-source BFS from the deepest nodes would work too.
    // Same as 1123. Lowest Common Ancestor of Deepest Leaves
    auto postorder = [](this auto&& postorder,
                        TreeNode* curr) -> std::pair<TreeNode*, int> {
      if (!curr) {
        return {nullptr, 0};
      }

      auto [lnode, ldepth] = postorder(curr->left);
      auto [rnode, rdepth] = postorder(curr->right);

      if (ldepth > rdepth) {
        return {lnode, ldepth + 1};
      }
      if (rdepth > ldepth) {
        return {rnode, rdepth + 1};
      }

      return {curr, ldepth + 1};
    };
    return postorder(root).first;
  }
};
