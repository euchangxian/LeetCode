#include <algorithm>
#include <cstddef>
#include <set>
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
  std::vector<int> treeQueries(TreeNode* root, std::vector<int>& queries) {
    // Each node is numbered [1..n]
    // Each query[i] is to remove the subtree rooted at node i, and return the
    // height of the resultant tree.
    // Each query is independent of each other.
    // Pre-processing the Tree would work, where at each node, store the pair
    // {leftSubtreeHeight, rightSubtreeHeight}, such that the height of the
    // tree rooted at the node is max(leftSubtreeHeight, rightSubtreeHeight).
    //
    // NOPE. There might be more than one subtree on either side that
    // contributes to the height of the current node..
    // It would be more correct to store {largestHeight, secondLargestHeight}
    // Essentially, at each level, store the two largest siblings/cousins.
    // Cousins of a node is defined as having the same depth, but different
    // parents.
    std::array<int, 100001> depths{};
    std::array<int, 100001> heights{};
    int n = 0;  // track largest node idx, i.e., number of nodes.
    getHeights(root, depths, heights, 0, n);

    // Depth, {{largestHeight, node1}, {secondLargestHeight, node2}}
    // Uses an orderedMultiSet to maintain the k largest elements, essentially a
    // PQ.
    std::array<std::multiset<int>, 100001> nodesByDepth{};

    // Process the depths/heights, getting the two largest on each level.
    for (int node = 1; node <= n; node++) {
      int depth = depths[node];
      int height = heights[node];

      auto& pq = nodesByDepth[depth];

      pq.emplace(height);
      if (pq.size() > 2) {
        pq.erase(pq.begin());
      }
    }

    std::vector<int> result;
    result.reserve(queries.size());
    for (int node : queries) {
      int depth = depths[node];
      int height = heights[node];

      auto& sameDepth = nodesByDepth[depth];

      // From here, there are three cases.
      // 1. The number of nodes at the depth is 1 => removing this node
      //    will result in depth-1
      // 2. The number of nodes is > 1 => Check if the current node's height
      //    is the largest, or secondLargest, or neither.
      //    2.1. If largest, return the secondLargest
      //    2.2. If not, then return the largest.
      if (sameDepth.size() == 1) {
        result.push_back(depth - 1);
      } else {
        int largestHeight = *sameDepth.rbegin();
        int secondLargestHeight = *sameDepth.begin();

        // NOTE: The current depth must be added to get the total height of the
        // tree after removal
        if (height == largestHeight) {
          // if largest, push second largest
          result.push_back(depth + secondLargestHeight);
        } else {
          result.push_back(depth + largestHeight);
        }
      }
    }
    return result;
  }

 private:
  int getHeights(TreeNode* root,
                 std::array<int, 100001>& depths,
                 std::array<int, 100001>& heights,
                 int depth,
                 int& n) {
    if (!root) {
      return -1;  // for null nodes
    }
    n = std::max(n, root->val);
    // To find siblings/cousins on the same depth
    depths[root->val] = depth;
    int height =
        1 + std::max(getHeights(root->left, depths, heights, depth + 1, n),
                     getHeights(root->right, depths, heights, depth + 1, n));
    heights[root->val] = height;
    return height;
  }
};
