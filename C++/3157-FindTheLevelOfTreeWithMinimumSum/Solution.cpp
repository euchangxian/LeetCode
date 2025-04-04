#include <climits>
#include <cstddef>
#include <queue>

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
  int minimumLevel(TreeNode* root) {
    long long minLevelSum = LLONG_MAX;
    int minLevel = 0;

    // Do a level order traversal
    std::queue<TreeNode*> frontier;
    frontier.push(root);
    int level = 0;
    while (!frontier.empty()) {
      std::size_t fSize = frontier.size();
      long long levelSum = 0;
      while (fSize--) {
        TreeNode* curr = frontier.front();
        frontier.pop();

        levelSum += curr->val;
        if (curr->left) {
          frontier.push(curr->left);
        }

        if (curr->right) {
          frontier.push(curr->right);
        }
      }
      ++level;

      if (levelSum < minLevelSum) {
        minLevelSum = levelSum;
        minLevel = level;
      }
    }

    return minLevel;
  }
};
