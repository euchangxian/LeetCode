#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;

  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

class Solution {
public:
  // Creating the Binary Tree is simple. Finding the root is not as simple.
  // A root will have no parent
  TreeNode *createBinaryTree(vector<vector<int>> &descriptions) {
    unordered_map<int, TreeNode *> nodes;
    unordered_set<int> childNodes;
    for (auto description : descriptions) {
      int parent = description[0];
      int child = description[1];
      bool isLeft = description[2];

      if (!nodes.count(parent)) {
        nodes[parent] = new TreeNode(parent);
      }
      if (!nodes.count(child)) {
        nodes[child] = new TreeNode(child);
      }
      childNodes.insert(child);

      // Construct the Binary Tree
      if (isLeft) {
        nodes[parent]->left = nodes[child];
      } else {
        nodes[parent]->right = nodes[child];
      }
    }

    TreeNode *root;
    for (auto const &[key, node] : nodes) {
      if (!childNodes.count(key)) {
        root = node;
        break;
      }
    }

    return root;
  }
};
