#include <vector>

#ifdef LOCAL
class Node {
 public:
  int val;
  std::vector<Node*> children;

  Node() {}

  Node(int _val) { val = _val; }

  Node(int _val, std::vector<Node*> _children) {
    val = _val;
    children = _children;
  }
};
#endif  // LOCAL

class Solution {
 private:
  void traverse(Node* curr, std::vector<int>& order) {
    if (!curr) {
      return;
    }

    for (const auto& neighbour : curr->children) {
      traverse(neighbour, order);
    }

    order.push_back(curr->val);
    return;
  }

 public:
  std::vector<int> postorder(Node* root) {
    std::vector<int> order;
    order.reserve(10e4);
    traverse(root, order);
    return order;
  }
};
