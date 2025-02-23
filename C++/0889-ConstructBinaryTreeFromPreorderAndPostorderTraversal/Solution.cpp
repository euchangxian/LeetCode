#include <cstddef>
#include <cstdlib>
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
  TreeNode* constructFromPrePost(std::vector<int>& preorder,
                                 std::vector<int>& postorder) {
    // preorder: root -> left -> right
    // postorder: left -> right -> root
    // preorder  = [1,2,4,5,3,6,7]
    // postorder = [4,5,2,6,7,3,1]
    // DFS? The nodes to the left of the preorder root, in the postorder array
    // are the left/right child.
    // If empty or already seen, then the node is a leaf node?
    // How to determine left/right though?
    // From the preorder? Assign left first, if there are nodes to the left in
    // the postorder?
    //
    // Or simpler...
    // Given that roots are seen last in the postorder traversal, we can assign
    // left subtree until preorder[preIdx] is equal to postorder[postIdx],
    // then assign the right subtree recursively.
    int preIdx = 0, postIdx = 0;
    return dfs(preorder, postorder, preIdx, postIdx);
  }

 private:
  TreeNode* dfs(const std::vector<int>& preorder,
                const std::vector<int>& postorder,
                int& preIdx,
                int& postIdx) {
    TreeNode* root = new TreeNode(preorder[preIdx++]);
    if (root->val != postorder[postIdx]) {
      root->left = dfs(preorder, postorder, preIdx, postIdx);
    }
    if (root->val != postorder[postIdx]) {
      root->right = dfs(preorder, postorder, preIdx, postIdx);
    }

    ++postIdx;
    return root;
  }
};
