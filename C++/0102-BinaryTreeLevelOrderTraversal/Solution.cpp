#include <queue>
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
  std::vector<std::vector<int>> levelOrder(TreeNode* root) {
    if (!root) {
      return {};
    }
    // BFS
    std::vector<std::vector<int>> result;
    std::queue<std::vector<TreeNode*>> frontiers;
    frontiers.push({root});
    while (!frontiers.empty()) {
      std::vector<TreeNode*> frontier = frontiers.front();
      frontiers.pop();

      std::vector<int> level;
      std::vector<TreeNode*> next;
      for (TreeNode*& node : frontier) {
        level.push_back(node->val);

        if (node->left) {
          next.push_back(node->left);
        }
        if (node->right) {
          next.push_back(node->right);
        }
      }

      result.push_back(std::move(level));

      if (!next.empty()) {
        frontiers.push(std::move(next));
      }
    }
    return result;
  }
};
