#include <stack>
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
  bool twoSumBSTs(TreeNode* root1, TreeNode* root2, int target) {
    // Return true iff there is a node in the first tree, and a node in the
    // second tree whose values sum up to a given integer target.
    //
    // Hm. How do we exploit the BST property.
    // Start from Root, move left/right, two-pointer-ish.
    // But how do we decide which pointer to move left/right?
    std::stack<TreeNode*> tree1;
    std::stack<TreeNode*> tree2;

    while (true) {
      while (root1 != nullptr) {
        tree1.emplace(std::exchange(root1, root1->left));
      }

      while (root2 != nullptr) {
        tree2.emplace(std::exchange(root2, root2->right));
      }

      if (tree1.empty() || tree2.empty()) {
        return false;
      }

      auto* node1 = tree1.top();
      auto* node2 = tree2.top();

      auto sum = node1->val + node2->val;
      if (sum == target) {
        return true;
      }
      if (sum < target) {
        tree1.pop();
        root1 = node1->right;  // add successor
      } else {
        tree2.pop();
        root2 = node2->left;  // add predecessor
      }
    }
    std::unreachable();
  }
};
