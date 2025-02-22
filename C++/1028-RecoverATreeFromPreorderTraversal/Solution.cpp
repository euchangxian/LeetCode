#include <cstddef>
#include <cstdlib>
#include <string_view>

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
  TreeNode* recoverFromPreorder(std::string_view traversal) {
    // Preorder: root -> left -> right
    // At each node, output D dashes, where D is the depth of this node, then
    // output the value.
    // If a node has only 1 child, that child is guaranteed to be the left
    // child.
    // Recover and return the root.
    // Naively, DFS, using the count of dashes as a way to indicate whether or
    // not to return from this branch. Hm...
    // I.e., if equal to expected D_child, then return val, else return nullptr?
    int idx = 0;
    return dfs(traversal, 0, idx);
  }

 private:
  TreeNode* dfs(std::string_view traversal, int expected, int& idx) {
    if (idx >= traversal.size()) {
      return nullptr;
    }

    int dashes = 0;
    while (idx < traversal.size() && traversal[idx] == '-') {
      ++dashes;
      ++idx;
    }  // idx should be pointing to a digit now

    // Hm, Some form of backtracking seems necessary? I.e., walk-back the idx.
    // Otherwise, the count of dashes will be lost
    if (dashes != expected) {
      idx -= dashes;
      return nullptr;
    }

    int x = 0;
    while (idx < traversal.size() && std::isdigit(traversal[idx])) {
      x = x * 10 + traversal[idx] - '0';
      ++idx;
    }  // idx should be pointing to a dash
    TreeNode* node = new TreeNode(x);

    // DFS left and right child
    // Note that idx is a shared reference.
    // Also, note that idx should be pointing to the next dash, due to the
    // digits parsing.
    node->left = dfs(traversal, expected + 1, idx);
    node->right = dfs(traversal, expected + 1, idx);

    return node;
  }
};
