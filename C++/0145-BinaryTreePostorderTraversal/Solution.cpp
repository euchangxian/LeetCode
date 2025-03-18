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
  std::vector<int> postorderTraversal(TreeNode* root) {
    std::vector<int> order;
    order.reserve(100);

    postorder(order, root);
    return order;
  }

 private:
  void postorder(std::vector<int>& order, TreeNode* curr) {
    if (!curr) {
      return;
    }

    postorder(order, curr->left);
    postorder(order, curr->right);
    order.push_back(curr->val);
    return;
  }
};
