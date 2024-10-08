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
class Solution {
 public:
  int findDuplicate(vector<int>& nums) {
    // The trick is to model the nums array as a Linked List, where the nodes
    // are the indices [0..n]. Edges would then be represented by nums[i],
    // where nums[i] represents a directed edge from i to nums[i].
    //
    // Thus, a duplicate number will result in a node having two incoming
    // edges. This node will be the start of a cycle.
    //
    // Floyd's Cycle detection algorithm can then be used to detect the cycle,
    // which consists of two phases:
    // 1. Initialize two pointers, one slow, one fast. Iterate until the slow
    //    and the fast pointers intersect. Call this point M.
    // 2. Initialize another slow pointer at index 0. Iterate the two slow
    //    pointers until they intersect. This intersection will be the start
    //    of the cycle, X.
    //
    // Suppose that the distance from the start point to the cycle is x, and
    // the distance from the cycle entrance X to the initial meeting point M
    // is y.
    // The total distance travelled by the slow pointer in Phase 1 is (x + y).
    // The total distance travelled by the fast pointer is 2(x + y)
    //
    // The difference between these two distances is then c, which must be a
    // multiple of the cycle length.
    //
    // Therefore, we can represent the distance travelled as:
    // 2(x + y) - (x + y) = k * c, where k is some integer >= 0
    // x + y = kc
    //
    // This means that the distance from the start point to the cycle's start
    // point is equal to traversing the cycle some number of times, as found
    // by the fast pointer.
    //
    // Phase 2 Explanation:
    // In Phase 2, we're specifically finding the entrance to the cycle (X),
    // which represents the duplicate number. We start one pointer (slow2) at
    // the beginning (index 0) and keep the other pointer (slow1) at the
    // meeting point M found in Phase 1. We move both pointers at the same
    // speed until they meet.
    //
    // Why this works:
    // After Phase 1, we know that: x + y = kc
    // Rewriting, we have: x = kc - y
    // This means the distance from the start to X (which is x) is equal to
    // the distance from M to X (which is kc - y, or simply x).
    //
    // Visualized:
    // 0 ---x--- X ---y--- M
    //         |           |
    //         |           |
    //         -------------
    //
    // In Phase 2:
    // - slow2 travels distance x from 0 to X
    // - slow1 travels distance x from M to X (possibly wrapping around the
    // cycle) They meet at X because they travel the same distance at the same
    // speed. X is our duplicate number, as it's the only number pointed to by
    // multiple indices.
    int slow1 = 0;
    int fast = 0;
    do {
      slow1 = nums[slow1];
      fast = nums[nums[fast]];
    } while (slow1 != fast);

    int slow2 = 0;
    while (slow2 != slow1) {
      slow1 = nums[slow1];
      slow2 = nums[slow2];
    }

    return slow1;  // or slow2
  }
};
