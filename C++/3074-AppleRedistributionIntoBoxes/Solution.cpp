#include <algorithm>
#include <functional>
#include <vector>

class Solution {
 public:
  int minimumBoxes(std::vector<int>& apple, std::vector<int>& capacity) {
    // apple of size n, capacity of size m
    // n packs, ith pack contain apple[i] apples.
    // m boxes, ith box has capacity[i] capacity.
    // Return minimum number of boxes required to redistribute n packs of apples
    // into boxes.
    const auto m = static_cast<int>(capacity.size());
    std::ranges::sort(capacity, std::greater<>{});
    auto sum = std::ranges::fold_left(apple, 0, std::plus<>{});

    int result = 0;
    for (auto cap : capacity) {
      sum -= cap;
      ++result;
      if (sum <= 0) {
        break;
      }
    }
    return result;
  }
};
