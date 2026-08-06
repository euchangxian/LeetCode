#include <algorithm>
#include <array>
#include <ranges>
#include <vector>

constexpr auto MAX_N = 100;
constexpr auto MAX_T = 10;
constexpr auto PRODUCT = []() {
  std::array<int, MAX_N + 1> product{};
  for (auto x : std::views::iota(1, MAX_N + 1)) {
    auto prod = 1;

    for (auto y = x; y; y /= 10) {
      prod *= y % 10;
    }
    product[x] = prod;
  }
  return product;
}();

static const auto DIVISORS = []() {
  std::array<std::vector<int>, MAX_T + 1> divisors{};
  for (auto x : std::views::iota(1, MAX_N + 1)) {
    auto prod = PRODUCT[x];
    for (auto t : std::views::iota(1, MAX_T + 1)) {
      if (prod % t == 0) {
        divisors[t].push_back(x);
      }
    }
  }
  return divisors;
}();

class Solution {
 public:
  int smallestNumber(int n, int t) {
    // Return smallest number >= n such that the product of its digits is
    // divisible by t.
    //
    // Brute force?
    const auto& divisors = DIVISORS[t];
    return *std::ranges::lower_bound(divisors, n);
  }
};
