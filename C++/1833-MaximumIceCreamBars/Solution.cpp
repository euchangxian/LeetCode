#include <algorithm>
#include <array>
#include <vector>

class Solution {
 public:
  int maxIceCream(std::vector<int>& costs, int coins) {
    // n ice cream bars.
    // costs[i] is the price of the ith ice cream bar.
    // start with coins, buy in any order as much ice cream bars.
    // Return the maximum number of ice cream bars that can be bought.
    //
    // "Must solve by Counting Sort".
    // costs[i] <= 1E5.
    constexpr std::size_t MAX_VAL = 1E5;
    std::array<int, MAX_VAL + 1> freq{};
    auto maxVal = 0;
    for (auto x : costs) {
      ++freq[x];
      maxVal = std::max(maxVal, x);
    }

    auto result = 0;
    for (auto cost = 1; cost <= maxVal; ++cost) {
      if (freq[cost] == 0) {
        continue;
      }

      if (coins < cost) {
        break;
      }

      auto count = std::min(freq[cost], coins / cost);
      coins -= cost * count;
      result += count;
    }
    return result;
  }
};
