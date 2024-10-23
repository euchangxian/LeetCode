#include <cstddef>
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
 public:
  // First glance seems pretty difficult. Naive Level Order traversal would not
  // work, since we want the sum of nodes that have different parents.
  //
  // One insight is that, given that the input is a single connected Binary
  // Tree, suppose that the root is level 1, then the sum will only be apparent
  // at level 3, where there are two distinct subtrees with > 1 nodes each.
  //
  // One thing that is needed is some kind of way to lookup a node that has
  // been traversed already, so its value can be updated with the sum of its
  // cousins. Might be two passes, a hash map, etc..
  //
  // Given that we have a level sum, how can we collect the nodes on a level
  // such that we can determine its siblings/cousins? With the levelSum, only
  // the node's siblings is necessary. This is because levelSum - siblingSum is
  // equal to cousinSum.
  //
  // This requires knowing the parent of each node in advance. As such, we can
  // first determine the levelSum of the NEXT level. This allows us to collect
  // the parent nodes. If two nodes share the same parent in a Binary Tree,
  // then they are siblings.
  TreeNode* replaceValueInTree(TreeNode* root) {
    // No cousins.
    // Update the levelSum in advance.
    root->val = 0;

    std::queue<TreeNode*> frontier;
    frontier.push(root);
    while (!frontier.empty()) {
      int n = frontier.size();

      // To collect nodes on THIS level.
      vector<TreeNode*> parents;
      parents.reserve(n);

      // NOTE: Get the level sum of the NEXT level.
      int levelSum = 0;
      while (n--) {
        TreeNode* curr = frontier.front();
        frontier.pop();

        // To be processed later.
        parents.push_back(curr);

        if (curr->left) {
          levelSum += curr->left->val;
          frontier.push(curr->left);
        }
        if (curr->right) {
          levelSum += curr->right->val;
          frontier.push(curr->right);
        }
      }

      for (TreeNode* parent : parents) {
        int siblingSum = 0;
        if (parent->left) {
          siblingSum += parent->left->val;
        }

        if (parent->right) {
          siblingSum += parent->right->val;
        }

        int cousinSum = levelSum - siblingSum;

        // Update step
        if (parent->left) {
          parent->left->val = cousinSum;
        }
        if (parent->right) {
          parent->right->val = cousinSum;
        }
      }
    }
    return root;
  }
};
