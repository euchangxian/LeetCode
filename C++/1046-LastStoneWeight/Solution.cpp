#include <functional>
#include <queue>
#include <vector>

class Solution {
 public:
  int lastStoneWeight(std::vector<int>& stones) {
    // In each round, choose the two heaviest stone and smash them together
    // That means we need a max heap
    std::priority_queue<int, std::vector<int>, std::less<int>> pq;

    for (int stone : stones) {
      pq.push(stone);
    }

    while (pq.size() > 1) {
      int y = pq.top();
      pq.pop();
      int x = pq.top();
      pq.pop();

      if (y - x) {
        pq.push(y - x);
      }
    }

    if (pq.empty()) {
      return 0;
    }

    return pq.top();
  }
};
