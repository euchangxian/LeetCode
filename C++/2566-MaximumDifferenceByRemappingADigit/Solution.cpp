#include <array>
#include <charconv>

class Solution {
 public:
  int minMaxDifference(int num) {
    // Given num.
    // Bob will sneakily remap one of the 10 possible digits to another digit.
    // Return the maximum difference between the minimum and maximum values
    // Bob can make, by remapping exactly one digit.
    //
    // Just remap the digit at the MSB if it is not already the max/min?
    // Trivial if converted to std::string.
    std::array<char, 9> buffer;  // num <= 1e8, allocate one more to simplify
    auto result =
        std::to_chars(buffer.data(), buffer.data() + buffer.size(), num);
    const std::size_t n = result.ptr - buffer.data();

    auto transform = [&](char digit) -> int {
      int result = 0;
      int i = 0;
      while (i < n && buffer[i] == digit) {
        result = (result * 10) + (buffer[i] - '0');
        ++i;
      }

      char map = buffer[i];  // possible OOB if only 8 chars allocated
      for (; i < n; ++i) {
        result *= 10;
        if (buffer[i] == map) {
          result += (digit - '0');
        } else {
          result += (buffer[i] - '0');
        }
      }
      return result;
    };

    return transform('9') - transform('0');
  }
};
