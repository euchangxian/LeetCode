#include <array>
#include <utility>

constexpr auto DIGITS = 10;

constexpr auto isBalanced = [](int n) {
  std::array<int, DIGITS> freq{};
  while (n) {
    ++freq[n % 10];
    n /= 10;
  }

  for (int d = 0; d < DIGITS; ++d) {
    if (freq[d] > 0 && d != freq[d]) {
      return false;
    }
  }
  return true;
};

class Solution {
 public:
  int nextBeautifulNumber(int n) {
    // An integer x is balanced if for every digit d in the number x, there are
    // exactly d occurences of that digit.
    // Given n, return the smallest balanced number greater than n.
    //
    // Hm. There are three operations:
    // 1. Replace digit x there occur more than x times, to digit y that
    //    occur less than y times, or vice versa.
    //    x -> y if x < y,
    //    y -> x if y can be reduced to 0, and y < x
    // 2. Add digit x to make up x occurences.
    //
    // Sigh. Given n <= 1E6, we can enumerate...
    for (int i = n + 1; i <= 1224444; ++i) {
      if (isBalanced(i)) {
        return i;
      }
    }
    std::unreachable();
  }
};
