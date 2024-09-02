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
  bool isSameTree(TreeNode *p, TreeNode *q) {
    if (!p && !q) {
      return true;
    }
    if (p && !q || !p && q) {
      return false;
    }

    return (p->val == q->val) && isSameTree(p->left, q->left) &&
           isSameTree(p->right, q->right);
  }

public:
  bool isSubtree(TreeNode *root, TreeNode *subRoot) {
    if (!subRoot) {
      return true;
    }
    if (!root) {
      return false;
    }

    if (isSameTree(root, subRoot)) {
      return true;
    }

    return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
  }
};
