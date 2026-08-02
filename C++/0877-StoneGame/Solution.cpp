#include <vector>

class Solution {
 public:
  bool stoneGame(std::vector<int>& piles) {
    // Even number of piles of stones. Total sum is odd, so no ties.
    // Alice start first. Take the entire pile of stones from the end/beginning.
    // Most stones win.
    // True if Alice Wins, false if Bob wins.
    //
    // Alice can greedily take the greater of two ends each time. Trivial.
    return true;
  }
};
