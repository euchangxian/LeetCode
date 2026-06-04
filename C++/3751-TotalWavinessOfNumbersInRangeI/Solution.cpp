#include <algorithm>
#include <array>

constexpr std::size_t MAX_N = 1E5;

constexpr auto waviness = [](auto num) {
  auto n = 0;
  std::array<int, 6> digits{};
  while (num > 0) {
    digits[n++] = num % 10;
    num /= 10;
  }

  auto count = 0;
  for (int i = 1; i < n - 1; ++i) {
    // peak
    if (digits[i - 1] < digits[i] && digits[i] > digits[i + 1]) {
      ++count;
    }

    // valley
    if (digits[i - 1] > digits[i] && digits[i] < digits[i + 1]) {
      ++count;
    }
  }

  return count;
};

static inline auto prefix = [] {
  std::array<int, MAX_N + 1> prefix{};
  for (auto num = 101; num <= MAX_N; ++num) {
    prefix[num] = prefix[num - 1] + waviness(num);
  }
  return prefix;
}();

class Solution {
 public:
  int totalWaviness(int num1, int num2) {
    // inclusive range [num1..num2]
    // Waviness of a number is the total count of peaks and valleys:
    // - a digit is a peak if it is > neighbours
    // - valley if <
    // - first,last cannot be peak/valley.
    // - < 3 digits => waviness=0
    // Return the sum of waviness for the range.
    //
    // 1 <= num1 <= num2 <= 1E5.
    return prefix[num2] - prefix[std::max(num1 - 1, 0)];
  }
};
