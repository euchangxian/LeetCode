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
  TreeNode *left;
  TreeNode *right;

  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

using namespace std;
class Solution {
public:
  vector<int> rightSideView(TreeNode *root) {
    if (!root) {
      return {};
    }

    vector<int> result;
    result.reserve(100);

    queue<TreeNode *> level;
    level.push(root);
    while (!level.empty()) {
      int size = level.size();
      for (int i = 0; i < size - 1; ++i) {
        auto curr = level.front();
        level.pop();

        if (curr->left) {
          level.push(curr->left);
        }

        if (curr->right) {
          level.push(curr->right);
        }
      }

      auto rightMost = level.front();
      level.pop();
      if (rightMost->left) {
        level.push(rightMost->left);
      }
      if (rightMost->right) {
        level.push(rightMost->right);
      }

      result.emplace_back(rightMost->val);
    }

    return result;
  }
};
