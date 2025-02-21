#include <bitset>
#include <cstddef>
#include <cstdlib>

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

// root value is 0
// for any tree node, if node.val == x and
// - node.left is not null, then node.left.val = 2*x+1
// - node.right is not null, then node.right.val = 2*x+2
//
// Recover from all nodes initialized to -1.
constexpr int MAX_VAL = 1000000;
class FindElements {
 public:
  FindElements(TreeNode* root) { dfs(root, 0); }

  bool find(int target) { return seen[target]; }

 private:
  std::bitset<MAX_VAL + 1> seen{};

  void dfs(TreeNode* root, int x) {
    if (!root) {
      return;
    }

    root->val = x;
    if (x <= MAX_VAL) {
      seen[x] = true;
    }

    if (root->left) {
      dfs(root->left, (x << 1) + 1);
    }

    if (root->right) {
      dfs(root->right, (x + 1) << 1);
    }
  }
};

/**
 * Your FindElements object will be instantiated and called as such:
 * FindElements* obj = new FindElements(root);
 * bool param_1 = obj->find(target);
 */
