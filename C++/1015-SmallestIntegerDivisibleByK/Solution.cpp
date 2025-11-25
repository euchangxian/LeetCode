#include <bitset>
#include <utility>

constexpr int MAX_K = 1E5;
class Solution {
 public:
  int smallestRepunitDivByK(int k) {
    // Given positive integer k, find the length of the smallest positive
    // integer n such that n is divisible by k and n only contains digit 1.
    // Return the length, else -1.
    // n may not fit in a 64-bit integer.
    //
    // Seems like modulo arithmetic.
    // n % k == 0
    // Length of n is minimally length of k.
    // If we see a repeated remainder, we can terminate.
    std::bitset<MAX_K> seen{};

    int n = 0;
    int length = 0;
    while (true) {
      n = ((10 * n) + 1) % k;
      ++length;

      if (n == 0) {
        return length;
      }

      if (seen.test(n)) {
        return -1;
      }
      seen.set(n);
    }

    std::unreachable();
  }
};
