#include <algorithm>
#include <limits>

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
  int maxPathSum(TreeNode* root) {
    // Find the maximum path sum. The path does not need to pass through the
    // root.
    // This is essentially DP on a DAG, where we can get the maximum path sum
    // passing through this node i as the root.
    // memo[i] = std::max(memo[i], memo[left] + memo[right] + val)
    // Though, we do not have the indexed representation of the Tree.
    // Hm. PostOrder?
    // sum = postorder(left) + val + postorder(right)
    // max = max(max, sum)
    // return sum
    // Take the max as we unroll the stack.
    // hm. We need to carefully update the sums/maxSums, since we may want to
    // exclude left/right child sums.
    // This can be done by excluding negative paths.
    int maxSum = std::numeric_limits<int>::min();
    postorder(root, maxSum);
    return maxSum;
  }

 private:
  int postorder(TreeNode* root, int& maxSum) {
    if (!root) {
      return 0;
    }

    int left = std::max(postorder(root->left, maxSum), 0);
    int right = std::max(postorder(root->right, maxSum), 0);

    maxSum = std::max(maxSum, left + root->val + right);

    // NOTE: We cannot return left + val + right. This is because the path
    // from an ancestor node can only explore either this node's left child, or
    // right child, NOT both.
    return std::max(left + root->val, root->val + right);
  }
};
