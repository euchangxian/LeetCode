#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Node {
public:
  int val;
  vector<Node *> children;

  Node() {}

  Node(int _val) { val = _val; }

  Node(int _val, vector<Node *> _children) {
    val = _val;
    children = _children;
  }
};

class Solution {
private:
  void traverse(Node *curr, vector<int> &order) {
    if (!curr) {
      return;
    }

    for (auto const &neighbour : curr->children) {
      traverse(neighbour, order);
    }

    order.push_back(curr->val);
    return;
  }

public:
  vector<int> postorder(Node *root) {
    vector<int> order;
    order.reserve(10e4);
    traverse(root, order);
    return order;
  }
};
