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
  int diameter(TreeNode* curr, int& result) {
    if (!curr) {
      return 0;
    }

    int left = diameter(curr->left, result);
    int right = diameter(curr->right, result);

    result = max(result, left + right);
    return 1 + max(left, right);
  }

 public:
  int diameterOfBinaryTree(TreeNode* root) {
    int result = 0;
    diameter(root, result);
    return result;
  }
};
