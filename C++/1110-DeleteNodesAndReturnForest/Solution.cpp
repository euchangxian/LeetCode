#include <unordered_set>
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
  std::vector<TreeNode*> delNodes(TreeNode* root, std::vector<int>& to_delete) {
    std::vector<TreeNode*> forest;
    forest.reserve(1000);

    std::unordered_set<int> toDelete =
        std::unordered_set<int>(to_delete.begin(), to_delete.end());

    root = deleteNodes(root, toDelete, forest);

    // handle the case where the root is not deleted
    if (root) {
      forest.push_back(root);
    }

    return forest;
  }

 private:
  TreeNode* deleteNodes(TreeNode* current,
                        const std::unordered_set<int>& toDelete,
                        std::vector<TreeNode*>& forest) {
    if (current == nullptr) {
      return nullptr;
    }

    current->left = deleteNodes(current->left, toDelete, forest);
    current->right = deleteNodes(current->right, toDelete, forest);

    if (toDelete.count(current->val)) {
      // If a parent node is deleted, its children become disjointed
      if (current->left) {
        forest.push_back(current->left);
      }

      if (current->right) {
        forest.push_back(current->right);
      }

      delete current;
      return nullptr;
    }

    return current;
  }
};
