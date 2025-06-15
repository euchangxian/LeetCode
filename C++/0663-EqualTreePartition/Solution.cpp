#include <unordered_map>

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
  bool checkEqualTree(TreeNode* root) {
    // Given root of binary tree, return true if the tree can be partitioned
    // into two trees with equal sums of values after removing exactly one
    // edge.
    // If the value of a subtree is half the total, then we found a
    // valid partition.
    std::unordered_map<int, int> seen;
    auto dfs = [&](this auto&& dfs, auto root) {
      if (!root) {
        return 0;
      }

      auto sum = dfs(root->left) + dfs(root->right) + root->val;
      ++seen[sum];
      return sum;
    };

    auto sum = dfs(root);
    if (sum % 2 != 0) {
      return false;
    }

    --seen[sum];  // must remove at least one.
    return seen[sum / 2] > 0;
  }
};
