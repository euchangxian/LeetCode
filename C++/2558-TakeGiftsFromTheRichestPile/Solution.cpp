#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <numeric>
#include <vector>

class Solution {
 public:
  long long pickGifts(std::vector<int>& gifts, int k) {
    // max heap
    std::make_heap(gifts.begin(), gifts.end());

    while (k--) {
      int leave = std::sqrt(gifts[0]);
      std::pop_heap(gifts.begin(), gifts.end());
      gifts.back() = leave;
    }

    return std::reduce(gifts.begin(), gifts.end(), 0LL, std::plus<>{});
  }
};
