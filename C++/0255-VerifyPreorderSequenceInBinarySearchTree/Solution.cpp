#include <limits>
#include <stack>
#include <vector>

class Solution {
 public:
  bool verifyPreorder(std::vector<int>& preorder) {
    // given unique sequence of numbers preorder, verify if it is correct
    // for a BINARY SEARCH tree.
    // A BST has a sorted inorder traversal.
    // Preorder: node -> left -> right
    // Also, given two traversals, it is always possible to recover the unique
    // tree.
    //
    // Recursively, we can divide the inorder into two halves, rooting at the
    // node in the preorder traversal.
    // Ensure the sorted property is adhered to.
    const int n = preorder.size();

    int subtreeMinimum = std::numeric_limits<int>::min();

    // Monotonically decreasing stack.
    std::stack<int> stk;
    for (int x : preorder) {
      while (!stk.empty() && stk.top() < x) {
        subtreeMinimum = stk.top();
        stk.pop();
      }

      if (x <= subtreeMinimum) {
        return false;
      }
      stk.push(x);
    }
    return true;
  }
};
