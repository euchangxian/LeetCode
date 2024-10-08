#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
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

using namespace std;
class Solution {
 public:
  vector<vector<int>> levelOrder(TreeNode* root) {
    if (!root) {
      return {};
    }
    // BFS
    vector<vector<int>> result;
    queue<vector<TreeNode*>> frontiers;
    frontiers.push({root});
    while (!frontiers.empty()) {
      vector<TreeNode*> frontier = frontiers.front();
      frontiers.pop();

      vector<int> level;
      vector<TreeNode*> next;
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
