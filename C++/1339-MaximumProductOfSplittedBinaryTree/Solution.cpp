#include <algorithm>
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

constexpr int MOD = 1E9 + 7;

class Solution {
 public:
  int maxProduct(TreeNode* root) {
    // Split the binary tree into two subtrees by removing one edge such that
    // the product of the sums is maximised.
    // Return the maximum product of the sums modulo 1E9+7.
    //
    // Can we decide what kind of split gives us the maximum product?
    // i.e., given sum of the tree = 10, splitting it 9:1, 8:2, 7:3, ...5:5,...
    // Seems like the closer the sums are, the greater the product?
    //
    // Determine sum(left) + val + sum(right) at each node.
    // Then, in the second iteration, check sum(left)+val vs sum(right)+val
    // Can just brute force again. 2 O(N).

    // sum of subtree at node
    std::vector<int> sums;
    auto dfs = [&](this auto&& dfs, TreeNode* node) {
      if (!node) {
        return 0LL;
      }
      auto total = dfs(node->left) + node->val + dfs(node->right);
      sums.push_back(total);
      return total;
    };

    long long total = dfs(root);
    long long result = 0;
    for (long long sum : sums) {
      result = std::max(result, sum * (total - sum));
    }
    return result % MOD;
  }
};
