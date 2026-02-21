#include <array>
#include <bitset>

constexpr auto isPrime = []() {
  std::bitset<32> isPrime{};
  std::array primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
  for (auto x : primes) {
    isPrime.set(x);
  }
  return isPrime;
}();

class Solution {
 public:
  int countPrimeSetBits(int left, int right) {
    // return the count of numbers in the inclusive range [left, right] that
    // have a prime number of set bits in their binary representation.
    int count = 0;
    for (int x = left; x <= right; ++x) {
      count += isPrime[__builtin_popcount(x)];
    }
    return count;
  }
};
