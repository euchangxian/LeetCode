#include <algorithm>
#include <cstddef>
#include <functional>
#include <vector>

using namespace std;
class Solution {
 public:
  int minStoneSum(vector<int>& piles, int k) {
    int remainingStones = std::reduce(piles.begin(), piles.end(), 0, plus<>{});

    std::make_heap(piles.begin(), piles.end());
    while (k--) {
      const int pile = piles.front();
      const int removed = static_cast<double>(pile) / 2.0;

      std::pop_heap(piles.begin(), piles.end());
      remainingStones -= removed;

      // Technically, integer division is sufficient.
      piles.back() = pile - removed;
      std::push_heap(piles.begin(), piles.end());
    }

    return remainingStones;
  }
};
