#include <cstddef>
#include <stack>
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

/**
 * Represents an iterator over the in-order traversal of a Binary SEARCH Tree.
 * Naively, when the Iterator is constructed, collect the in-order traversal of
 * the elements into an array. This allows next and hasNext to run in O(1) time.
 *
 * But memory is limited to O(h), where h is the height of the tree (O(logn)).
 * This means we must lazily initialize the in-order traversal of the tree.
 * How?
 * Instead of using the call-stack to recurse, use a Stack instead.
 *
 * This means we need to store all nodes in the left path, resulting in O(h)
 * space.
 */
class BSTIterator {
 private:
  int idx;
  vector<int> inorder;
  std::stack<TreeNode*> callStack;

  void traverseLeft(TreeNode* root) {
    while (root) {
      callStack.push(root);
      root = root->left;
    }
  }

 public:
  /**
   * The pointer should be initialized to a non-existent number smaller than
   * any element in the BST. i.e., -1
   */
  BSTIterator(TreeNode* root) {
    // Add the left path
    traverseLeft(root);
  }

  /**
   * Moves the pointer to the right, then returns the number at the pointer.
   * i.e., successor function.
   * Assume next() calls are always valid.
   */
  int next() {
    // Pop the top-most node from the stack. The value should be the minimum
    // value.
    // Then, traverse the left path with node->right as the root.
    TreeNode* top = callStack.top();
    callStack.pop();

    traverseLeft(top->right);
    return top->val;
  }

  /**
   * Returns true if there exists a number in the traversal to the right of
   * the pointer.
   */
  bool hasNext() { return !callStack.empty(); }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
