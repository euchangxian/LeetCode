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
private:
public:
  TreeNode *invertTree(TreeNode *root) {
    if (!root) {
      return nullptr;
    }

    TreeNode *left = invertTree(root->left);
    root->left = invertTree(root->right);
    root->right = left;
    return root;
  }
};