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
 private:
  int height(TreeNode* curr) {
    if (!curr) {
      return 0;
    }

    int leftHeight = height(curr->left);
    int rightHeight = height(curr->right);

    if (leftHeight == -1 || rightHeight == -1 ||
        abs(leftHeight - rightHeight) > 1) {
      return -1;
    }

    return max(leftHeight, rightHeight) + 1;
  }

 public:
  bool isBalanced(TreeNode* root) {
    int result = height(root);

    return result != -1;
  }
};
