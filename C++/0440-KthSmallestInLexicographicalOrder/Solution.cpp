#include <algorithm>
#include <array>
#include <bitset>
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
class Solution {
private:
  int countNodesBetween(int n, long long curr, long long next) const {
    int nodes{0};
    while (curr <= n) {
      // Takes the minimum of the number of nodes from curr to n,
      // and the number of nodes between curr and next
      // The gap between curr and next widens by a factor of 10 each iteration.
      // This is because each node has 10 children.
      //
      // E.g., n = 100, curr = 1, next = 2
      //   iter=1: curr = 1, next = 2,     => min(100, 1) => nodes = 1
      //   (accounts for the node 1 itself)
      //
      //   iter=2: curr = 10, next = 20,   => min(91, 10) => nodes = 11
      //   (accounts for 10, 11, ... 19)
      //
      //   iter=3: curr = 100, next = 200, => min(1, 100) => nodes = 12
      //   (accounts for the node 100)
      //
      // As demonstrated, the time complexity is O(logn) (base-10), since
      // we avoid traversing each individual node to check if its less than
      // or more than the kth children
      nodes += min(static_cast<long long>(n + 1) - curr, next - curr);

      curr *= 10;
      next *= 10;
    }

    return nodes;
  }

public:
  int findKthNumber(int n, int k) {
    // Find kth smallest lexicographically. Seems rather simple considering
    // 386-LexicographicalNumbers
    // BUT, the input constraints (k, n <= 10e9) require a better time
    // complexity than O(n)
    // How do we do better?
    // Instead of traversing each subtree one-by-one
    // i.e. 1 -> 10 -> 100 -> ...
    //           10 -> 101 -> ...
    //      2 -> 20 -> ...
    // We can prune the leaves of the tree smartly.
    // Consider two prefixes, e.g. 1 and 2.
    // The k-th smallest number will not be in the subtree rooted at 1 if the
    // number of nodes of the subtree rooted at 1 is less than k.
    // Therefore, we can prune 1 and its subtree and search for the kth smallest
    // at the subtree rooted at 2.
    //
    // Otherwise, if the number of nodes is greater than k, then the kth
    // smallest must be somewhere in the subtree rooted at 1.
    // We can go down one layer, to the subtree rooted at 10 and recursively
    // search for the kth smallest.
    //
    // Now, the key issue is how to count the number of nodes of a subtree
    // efficiently.
    int curr{1};
    --k;

    while (k > 0) {
      const int count = countNodesBetween(n, static_cast<long long>(curr),
                                          static_cast<long long>(curr + 1));

      if (count <= k) {
        k -= count;
        ++curr; // Not in the curr subtree.
      } else {
        --k; // remove the current root from the count, go to the next depth
        curr *= 10;
      }
    }
    return curr;
  }
};
