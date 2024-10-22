#include <cstddef>
#include <functional>
#include <queue>
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
class Solution {
 private:
 public:
  long long kthLargestLevelSum(TreeNode* root, int k) {
    // Use a minHeap, since we want the kth smallest among the large sums.
    std::priority_queue<long long, std::vector<long long>, std::greater<>>
        kthLargest;

    // Do a level order traversal
    std::queue<TreeNode*> frontier;
    frontier.push(root);
    while (!frontier.empty()) {
      size_t fSize = frontier.size();
      long long levelSum = 0LL;
      while (fSize--) {
        TreeNode* curr = frontier.front();
        frontier.pop();

        levelSum += curr->val;
        if (curr->left) {
          frontier.push(curr->left);
        }

        if (curr->right) {
          frontier.push(curr->right);
        }
      }

      kthLargest.push(levelSum);
      if (kthLargest.size() > k) {
        kthLargest.pop();
      }
    }

    if (kthLargest.size() < k) {
      return -1;
    }
    return kthLargest.top();
  }
};
