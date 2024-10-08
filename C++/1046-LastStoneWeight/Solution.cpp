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
  int lastStoneWeight(vector<int>& stones) {
    // In each round, choose the two heaviest stone and smash them together
    // That means we need a max heap
    priority_queue<int, vector<int>, less<int>> pq;

    for (auto const& stone : stones) {
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
