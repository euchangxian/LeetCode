#include <bitset>
#include <iterator>
#include <ranges>
#include <vector>

constexpr int MAX_VAL = 1E5;

constexpr std::bitset<MAX_VAL + 1> hasEven = []() {
  std::bitset<MAX_VAL + 1> hasEven;
  // for (int i = 0; i < 10; ++i) {
  //   hasEven[i] = 0;
  // }
  for (int i = 10; i < 100; ++i) {
    hasEven[i] = 1;
  }
  // for (int i = 100; i < 1000; ++i) {
  //   hasEven[i] = 0;
  // }
  for (int i = 1000; i < 10000; ++i) {
    hasEven[i] = 1;
  }
  // for (int i = 10000; i < 100000; ++i) {
  //   hasEven[i] = 0;
  // }
  hasEven[100000] = 1;
  return hasEven;
}();

class Solution {
 public:
  int findNumbers(std::vector<int>& nums) {
    return std::ranges::distance(
        std::ranges::views::filter(nums, [](int x) { return hasEven[x]; }));
  }
};
