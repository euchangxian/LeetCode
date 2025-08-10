#include <algorithm>
#include <array>

constexpr std::size_t BITS = 31;
constexpr std::size_t DIGITS = 10;

constexpr std::array<int, BITS> powOfTwos = []() {
  std::array<int, BITS> result{};
  result[0] = 1;
  for (int i = 1; i < BITS; ++i) {
    result[i] = result[i - 1] << 1;
  }
  return result;
}();

constexpr auto countDigits = [](int n) {
  std::array<int, DIGITS> frequency{};
  while (n) {
    auto d = n % 10;
    n /= 10;
    ++frequency[d];
  }
  return frequency;
};

constexpr std::array<std::array<int, DIGITS>, BITS> digitCount = []() {
  std::array<std::array<int, DIGITS>, BITS> counts{};
  for (int i = 0; i < BITS; ++i) {
    counts[i] = countDigits(powOfTwos[i]);
  }
  return counts;
}();

class Solution {
 public:
  bool reorderedPowerOf2(int n) {
    // Given integer n. Reorder the digits such that leading digit is not zero,
    // to make a power of 2.
    // Return true if possible.
    auto count = countDigits(n);
    return std::any_of(
        digitCount.begin(), digitCount.end(),
        [&count](const auto& target) { return count == target; });
  }
};
