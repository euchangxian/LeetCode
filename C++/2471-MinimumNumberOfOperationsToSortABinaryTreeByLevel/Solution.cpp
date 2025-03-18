#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <queue>
#include <utility>
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
  int minimumOperations(TreeNode* root) {
    // In one operation: choose any two nodes at the same level and swap their
    // values.
    // Minimum number of operations needed to make the values at each level
    // sorted in a strictly increasing order.
    // Level order is simple -> Do a level-order traversal. But how to count
    // the minimum number of swaps?
    // Each swap can sort two values at most. Sorts a single value at least.
    //
    // The two value case is when both values are in each other's sorted
    // position.
    // Hmmmm. Naively, sort at each level.
    std::queue<std::vector<TreeNode*>> frontier;
    frontier.push({root});

    int swaps = 0;
    while (!frontier.empty()) {
      std::vector<TreeNode*> currLevel = std::move(frontier.front());
      frontier.pop();
      swaps += minSwaps(currLevel);

      std::vector<TreeNode*> nextFrontier;
      nextFrontier.reserve(currLevel.size() * 2);
      for (TreeNode* node : currLevel) {
        if (node->left) {
          nextFrontier.push_back(node->left);
        }
        if (node->right) {
          nextFrontier.push_back(node->right);
        }
      }

      if (!nextFrontier.empty()) {
        frontier.push(std::move(nextFrontier));
      }
    }
    return swaps;
  }

 private:
  int minSwaps(std::vector<TreeNode*>& level) {
    const int n = level.size();

    // {value, originalIndex}
    std::vector<std::pair<int, int>> positions(n);
    for (int i = 0; i < n; ++i) {
      positions[i] = {level[i]->val, i};
    }
    std::sort(positions.begin(), positions.end());

    // cycle counting.
    std::vector<bool> visited(n, false);
    int swaps = 0;
    for (int i = 0; i < n; ++i) {
      if (visited[i] || positions[i].second == i) {
        // already in correct positions/visited.
        continue;
      }

      int cycleLength = 0;
      int j = i;
      while (!visited[j]) {
        visited[j] = true;
        j = positions[j].second;  // go to where this element should be at.
        ++cycleLength;
      }

      // k-1 swaps for a cycle of length k.
      swaps += (cycleLength - 1);
    }

    return swaps;
  }
};
