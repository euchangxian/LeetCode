#include <algorithm>
#include <functional>
#include <ranges>
#include <vector>

class Solution {
 public:
  long long maximumHappinessSum(std::vector<int>& happiness, int k) {
    // ith child has happiness[i]
    // Select k children from n childrens in k turns.
    // After selecting a child, the happiness value of all children not yet
    // selected decreases by 1.
    // happiness[i] cannot become negative.
    std::ranges::sort(happiness, std::greater<>{});

    long long result = 0;
    int taken = 0;
    for (auto x : happiness | std::views::take(k)) {
      result += std::max(x - taken, 0);
      ++taken;
    }
    return result;
  }
};
