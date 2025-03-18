#include <algorithm>
#include <cstddef>
#include <queue>
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
  bool flipEquiv(TreeNode* root1, TreeNode* root2) {
    if (!root1 && !root2) {
      return true;
    }

    if (!root1 || !root2) {
      return false;
    }

    if (root1->val != root2->val) {
      return false;
    }

    // This is not O(4^n), but O(h) (or O(n) if unabalanced binary tree).
    // This is because the question guarantees that the nodes are distinct.
    // Considering the decision tree, at most 2 of the 4 recursive calls will
    // exhaust the decision tree / go all the way to the bottom.
    bool noSwap = flipEquiv(root1->left, root2->left) &&
                  flipEquiv(root1->right, root2->right);

    bool swap = flipEquiv(root1->left, root2->right) &&
                flipEquiv(root1->right, root2->left);

    return noSwap || swap;
  }

  bool flipEquivWRONG(TreeNode* root1, TreeNode* root2) {
    // Seems similar to level order traversal. Just traverse one of the trees,
    // say root1, then check its children against root2's.
    // There are 3 cases:
    // Child value correspond. No flip.
    // Child value are flipped. Flip.
    // Child values do not match. Return false early.

    if (!root1 && !root2) {
      return true;
    }

    if (!root1 || !root2) {
      return false;
    }

    if (root1->val != root2->val) {
      return false;
    }

    std::queue<std::pair<TreeNode*, TreeNode*>> frontier;
    frontier.emplace(root1, root2);

    while (!frontier.empty()) {
      int n = frontier.size();
      auto [node1, node2] = frontier.front();
      frontier.pop();

      // Hm. How to enumerate all the cases cleanly?
      // if there are left and right for both
      if (node1->left && node2->left && node1->right && node2->right) {
        // Case 1: values match, just push
        // Case 2: values are inverted. Re-assign as necessary.
        // Case 3: values are not the same. Return false;

        if (node1->left->val == node2->left->val &&
            node1->right->val == node2->right->val) {
          frontier.emplace(node1->left, node2->left);
          frontier.emplace(node1->right, node2->right);
          continue;
        }

        if (node1->left->val == node2->right->val &&
            node1->right->val == node2->left->val) {
          std::swap(node1->left, node1->right);  // flip

          // push
          frontier.emplace(node1->left, node2->left);
          frontier.emplace(node1->right, node2->right);
          continue;
        }

        return false;
      }
      // Hm. For the case where there are only one children
      // For the case where the children are flipped
      if (node1->left && node2->right) {
        if (node1->left->val != node2->right->val) {
          return false;
        }
        std::swap(node1->left, node1->right);
        frontier.emplace(node1->right, node2->right);
        continue;
      }

      if (node1->right && node2->left) {
        if (node1->right->val != node2->left->val) {
          return false;
        }
        std::swap(node1->left, node1->right);
        frontier.emplace(node1->left, node2->left);
        continue;
      }

      // For the case where the childrens are equal, no flips needed.
      // Check that either left == left or right == right
      if (node1->left && node2->left) {
        if (node1->left->val != node2->left->val) {
          return false;
        }
        frontier.emplace(node1->left, node2->left);
      }

      if (node1->right && node2->right) {
        if (node1->right->val != node2->right->val) {
          return false;
        }
        frontier.emplace(node1->right, node2->right);
      }

      // Otherwise, check that both have no children.
      // Lol. NOT (node1 == nullptr && node2 == nullptr)
      if (!(!node1->left && !node2->left)) {
        return false;
      }

      if (!(!node1->right && !node2->right)) {
        return false;
      }
    }
    return true;
  }
};
