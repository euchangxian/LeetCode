#include <algorithm>
#include <climits>
#include <cstddef>
#include <cstdlib>
#include <queue>
#include <utility>
#include <vector>

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;

  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

class Solution {
 public:
  std::vector<int> largestValues(TreeNode* root) {
    // level order traversal + max element.
    if (!root) {
      return {};
    }

    std::queue<TreeNode*> frontier;
    frontier.push(root);

    std::vector<int> result;
    while (!frontier.empty()) {
      int size = frontier.size();
      std::queue<TreeNode*> nextFrontier;

      int max = INT_MIN;
      while (size--) {
        auto curr = frontier.front();
        frontier.pop();
        max = std::max(max, curr->val);

        if (curr->left) {
          nextFrontier.push(curr->left);
        }
        if (curr->right) {
          nextFrontier.push(curr->right);
        }
      }

      if (!nextFrontier.empty()) {
        frontier = std::move(nextFrontier);
      }
      result.push_back(max);
    }
    return result;
  }
};
