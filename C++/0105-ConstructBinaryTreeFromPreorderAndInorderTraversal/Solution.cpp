#include <algorithm>
#include <array>
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
  TreeNode *build(vector<int> const &preorder, vector<int> const &inorder,
                  unordered_map<int, int> &inorderIndex, int &preIdx,
                  int const inStart, int const inEnd) {
    if (inStart > inEnd) {
      return nullptr;
    }

    TreeNode *root = new TreeNode(preorder[preIdx]);
    int inorderIdx = inorderIndex[preorder[preIdx]];

    ++preIdx; // Passed by reference so that the left-recursive call will update

    root->left =
        build(preorder, inorder, inorderIndex, preIdx, inStart, inorderIdx - 1);
    root->right =
        build(preorder, inorder, inorderIndex, preIdx, inorderIdx + 1, inEnd);

    return root;
  }

public:
  TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
    // preorder: root, left, right
    // inorder: left, root, right
    // Therefore, traverse the preorder. The corresponding left and right
    // subtrees will be the left and right subarrays in the inorder.
    // E.g. preorder = [3, 9, 20, 15, 7], inorder = [9, 3, 15, 20, 7]
    // first iter: root = 3
    // leftSubtree = [9], rightSubtree = [15, 20, 7].
    // Recurse.
    // Therefore, we will need the index of the node in the inorder traversal.
    // An offset will also be needed to prevent copying of arrays. E.g.
    // when recursing onto the rightSubtree, the offset will be 2.

    // value : index map
    unordered_map<int, int> inorderIndex;
    for (int i = 0; i < inorder.size(); ++i) {
      inorderIndex[inorder[i]] = i;
    }

    int idx = 0;
    return build(preorder, inorder, inorderIndex, idx, 0, inorder.size() - 1);
  }
};
