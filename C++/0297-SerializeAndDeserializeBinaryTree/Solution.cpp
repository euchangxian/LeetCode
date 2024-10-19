#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

using namespace std;
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;

  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

/**
 * Serializing and Deserializing in Level-Order seems the most straightforward,
 * since the number of nodes at each level of the binary tree is simply 2^n.
 *
 * Another way would be to store two traversals of the binary tree, which allows
 * unique encoding/decoding of the binary tree structure. E.g., inorder and
 * preorder, or inorder and postorder, etc.
 *
 * However, reconstructing the tree from the traversals is less straightforward,
 * and is a LeetCode problem on its own.
 * E.g. LC 105 - Construct Binary Tree from Preorder and Inorder traversal.
 *
 * BUT. Since we have control over the encoding, we can insert NULLs. This means
 * that preorder traversal effectively becomes Level order-like traversal,
 * making serialization and deserialization simpler.
 */
class Codec {
 private:
  // or any non-digits
  static constexpr char nullRepr = '#';

  void encodePreorder(TreeNode* root, std::ostringstream& encoded) {
    if (!root) {
      encoded << nullRepr << ' ';
      return;
    }

    encoded << root->val << ' ';  // space delimited to simplify deserialization
    encodePreorder(root->left, encoded);
    encodePreorder(root->right, encoded);
  }

  // A stream maintains state of where the current pointer is.
  TreeNode* fromData(std::istringstream& data) {
    // The maximum length of a number is 5, since the max value is 1000, and
    // adding a negative sign is -1000 (5 chars). +1 to include the null
    // terminator
    char token[6];
    data >> token;

    if (token[0] == nullRepr) {
      return nullptr;
    }

    // Array to Integer, atoi
    TreeNode* root = new TreeNode(std::atoi(token));
    root->left = fromData(data);
    root->right = fromData(data);

    return root;
  }

 public:
  // Encodes a tree to a single string.
  string serialize(TreeNode* root) {
    std::ostringstream encoded;
    encodePreorder(root, encoded);
    return encoded.str();
  }

  // Decodes your encoded data to tree.
  TreeNode* deserialize(string data) {
    std::istringstream dataStream(std::move(data));

    return fromData(dataStream);
  }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
