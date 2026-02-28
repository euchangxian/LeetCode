#include <bit>

constexpr std::uint64_t MOD = 1E9 + 7;
class Solution {
 public:
  int concatenatedBinary(int n) {
    // Return the decimal value of the binary string formed by concatenating
    // the binary representation of 1..n in order, modulo 1e9+7.
    //
    // Do not actually have to simulate string concatenation.
    // We can shift the number by the number of bits added.
    // Modulo at every step.
    // How to count bits added? Count Leading Zeros
    // EDIT: std::bit_width = std::numeric_limits<T>::digits - std::countl_zero

    std::uint64_t result = 0;
    for (std::uint64_t i = 1; i <= n; ++i) {
      result = ((result << std::bit_width(i)) + i) % MOD;
    }

    return static_cast<int>(result);
  }
};
