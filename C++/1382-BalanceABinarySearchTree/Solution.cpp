#include <vector>

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
  TreeNode* balanceBST(TreeNode* root) {
    // Given the root of a BST, return a balanced binary search tree.
    // A BST is balanced if the depth of the two subtrees of every node never
    // differs by more than 1.
    //
    // Naively, collect and sort, then build the binary search tree?
    // Don't even have to sort. Inorder traversal.
    //
    // For building, middle, recurse left, then recurse right.
    std::vector<TreeNode*> nodes;
    auto inorder = [&nodes](this auto&& inorder, auto* node) {
      if (!node) {
        return;
      }
      inorder(node->left);
      nodes.push_back(node);
      inorder(node->right);
    };
    inorder(root);

    auto build = [](this auto&& build,
                    std::span<TreeNode*> nodes) -> TreeNode* {
      if (nodes.empty()) {
        return nullptr;
      }

      int mid = nodes.size() / 2;
      auto* root = nodes[mid];
      root->left = build(std::span{nodes.begin(), nodes.begin() + mid});
      root->right = build(std::span{nodes.begin() + mid + 1, nodes.end()});
      return root;
    };

    return build(nodes);
  }
};
