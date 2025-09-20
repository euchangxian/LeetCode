#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdint>
#include <deque>
#include <functional>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// Tree with N nodes numbered [0..n-1]
// parent[i]: parent of the ith node. root node 0 has parent[0] = -1
// lock: lock the given node for the given user, prevents other users from
//       locking the same node. Only unlocked nodes can be locked.
// unlock: unlock the given node for the given user. Only nodes locked by the
//       given user may be unlocked by the given user.
// upgrade: lock the given node for the given user, unlock all of its
//          descendents regardless of who locked it.
//          A node can only be upgraded if:
//          - the node is unlocked,
//          - it has at least one locked descendent,
//          - it does not have any locked ancestors.
//
// Wew. The problem is figuring out whether a certain node has locked
// descendents and locked ancestors. Traversing the tree each time will result
// in O(N) time operations if the tree is flat, i.e., a linked list.
class LockingTree {
 public:
  LockingTree(std::vector<int>& parent) {}

  bool lock(int num, int user) {}

  bool unlock(int num, int user) {}

  bool upgrade(int num, int user) {}
};

/**
 * Your LockingTree object will be instantiated and called as such:
 * LockingTree* obj = new LockingTree(parent);
 * bool param_1 = obj->lock(num,user);
 * bool param_2 = obj->unlock(num,user);
 * bool param_3 = obj->upgrade(num,user);
 */
