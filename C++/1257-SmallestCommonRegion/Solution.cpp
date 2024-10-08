#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
class Solution {
 public:
  string findSmallestRegion(vector<vector<string>>& regions,
                            string region1,
                            string region2) {
    // The key insight is the constraint "given r1, r2 and r3 such that r1
    // includes r3, it is guaranteed there is no r2 such that r2 includes r3".
    // This means that for any given node r3, there is at most a single
    // incoming edge to it.
    // Therefore, we can model it as a Tree problem, each node has at most one
    // parent.
    // With this, the problem can be reduced to a Lowest Common Ancestor
    // problem.
    // Naively, we can encapsulate each region in a TreeNode and build the Tree.
    // Can we do better?
    std::unordered_map<string, string> parents;
    for (const auto& region : regions) {
      for (size_t i = 1; i < region.size(); ++i) {
        parents[region[i]] = region[0];
      }
    }

    string* x = &region1;
    string* y = &region2;
    while (*x != *y) {
      auto itx = parents.find(*x);
      if (itx == parents.end()) {
        // Not in the same subtree
        x = &region2;
      } else {
        x = &itx->second;
      }

      auto ity = parents.find(*y);
      if (ity == parents.end()) {
        y = &region1;
      } else {
        y = &ity->second;
      }
    }

    return *x;
  }
};
