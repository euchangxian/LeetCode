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

using namespace std;
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;

  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

class Solution {
private:
  void postorder(vector<int> &order, TreeNode *curr) {
    if (!curr) {
      return;
    }

    postorder(order, curr->left);
    postorder(order, curr->right);
    order.push_back(curr->val);
    return;
  }

public:
  vector<int> postorderTraversal(TreeNode *root) {
    vector<int> order;
    order.reserve(100);

    postorder(order, root);
    return order;
  }
};
