#include <array>
#include <bitset>
#include <utility>

constexpr int MAX_N = 1E4;
constexpr std::array<int, 10> ROTATED{{0, 1, 5, -1, -1, 2, 9, -1, 8, 6}};

constexpr auto rotateDigit(int digit) {
  return std::make_pair(ROTATED[digit], ROTATED[digit] != -1);
};

constexpr auto isGood = [](int x) {
  int originalX = x;
  int y = 0;
  int multiplier = 1;
  while (x) {
    int digit = x % 10;
    x /= 10;

    auto [rotated, ok] = rotateDigit(digit);
    if (!ok) {
      return false;
    }

    y += multiplier * rotated;
    multiplier *= 10;
  }
  return originalX != y;
};

constexpr std::bitset<MAX_N + 1> GOOD_X = []() {
  std::bitset<MAX_N + 1> result;
  for (int i = 1; i <= MAX_N; ++i) {
    result[i] = isGood(i);
  }
  return result;
}();

constexpr std::array<int, MAX_N + 1> PREFIX = []() {
  std::array<int, MAX_N + 1> result{};
  for (int i = 1; i <= MAX_N; ++i) {
    result[i] = GOOD_X[i] + result[i - 1];
  }
  return result;
}();

class Solution {
 public:
  int rotatedDigits(int n) {
    // A number is good if after rotating each digit 180degree, we get a valid
    // number != x.
    // 0, 1, 8 rotate to themselves.
    // 2 and 5 rotate to each other.
    // 6 and 9 rotate to each other.
    // The others (3, 4, 7) become invalid.
    // Return the number of good integers in the range [1..n]
    // Note n<=1E4.
    return PREFIX[n];
  }
};
