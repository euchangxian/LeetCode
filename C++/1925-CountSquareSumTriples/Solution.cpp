#include <array>
#include <bitset>

constexpr int MAX_N = 250;
constexpr auto squares = []() {
  std::array<int, MAX_N + 1> result{};
  for (int i = 0; i <= MAX_N; ++i) {
    result[i] = i * i;
  }
  return result;
}();

constexpr auto isPerfect = []() {
  std::bitset<(MAX_N + 1) * (MAX_N + 1)> result;
  for (auto x : squares) {
    result[x] = true;
  }
  return result;
}();

class Solution {
 public:
  int countTriples(int n) {
    // A square triple (a, b, c) is a triple where a^2 + b^2 = c^2
    // Return the number of square triples such that 1 <= a, b, c <= n
    //
    // Pythagoras
    // Brute force
    const auto nSquared = n * n;
    int result = 0;
    for (int a = 1; a <= n; ++a) {
      for (int b = 1; b <= n; ++b) {
        auto cc = (a * a) + (b * b);

        if (cc <= nSquared && isPerfect[cc]) {
          ++result;
        }
      }
    }
    return result;
  }
};
