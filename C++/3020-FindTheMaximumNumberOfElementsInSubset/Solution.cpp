#include <algorithm>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  int maximumLength(std::vector<int>& nums) {
    // Positive integers nums.
    // Select a subset of nums that satisifies the following condition:
    // - Place the selected elements in a 0-indexed array such that it follows:
    //   [x, x^2, x^4, ... x^(k/2), x^k, x^(k/2), ... x^4, x^2, x]
    // - k can be any non-negative power of 2.
    // Return the maximum number of elements in a subset that satisifies these
    // conditions.
    //
    // - nums[i] <= 1E9
    // Second condition: k = {2^0=1, 2^1=2, 2^2=4, 2^3=8, ... 2^16=65,536, 2^30}
    // Thus we only need enumerate those.
    //
    // reuslt is at least the number of occurences of 1s, rounded down to odd,
    // since we can make {1, 1, ..., 1, 1}
    const auto n = static_cast<int>(nums.size());
    std::unordered_map<long long, int> count;
    count.reserve(n);
    for (auto x : nums) {
      ++count[x];
    }

    auto numOnes = count[1];
    auto result = numOnes - (1 - (numOnes & 1));
    count.erase(1);

    for (auto [num, _] : count) {
      auto subsetSize = 0;
      long long x = num;
      for (; count.contains(x) && count[x] > 1; x *= x) {
        subsetSize += 2;
      }

      result = std::max(result, subsetSize + (count.contains(x) ? 1 : -1));
    }
    return result;
  }
};
