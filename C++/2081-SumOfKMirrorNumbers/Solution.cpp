#include <vector>

using i64 = long long;

template <bool isOdd>
auto createPalindrome = [](i64 num) {
  i64 x = num;
  if constexpr (isOdd) {
    x /= 10;  // skip middle digit for odd palindromes
  }
  while (x > 0) {
    num = num * 10 + (x % 10);
    x /= 10;
  }
  return num;
};

class Solution {
 public:
  i64 kMirror(int k, int n) {
    // A K-mirror number is a positive integer that is a palindrome in both
    // base-10 AND base-k.
    // Given base k and number n, return the sum of the n smallest k-mirror
    // numbers.
    //
    // Constraints:
    // 2 <= k <= 9
    // 1 <= n <= 30
    // Looking at the example k=7, n=17, the largest number is nearly 7E6.
    // Enumerating through mirrors of base-k, then checking if its base-10
    // representation is a mirror is feasible.
    // Base-10 too.
    //
    // In terms of digit positions, the LSB alone is always a k-mirror.
    // Then, with two digits, it will be 11,..., (k-1)(k-1).
    // with three, we have 101, 111, ...,
    // Also, this maintains the smallest-n property.
    // How to generalise this pattern?
    // Iterate through number of digits, then recurse/enumerate from outwards?

    auto isKPalindrome = [k](i64 x) {
      std::vector<int> digits;
      while (x > 0) {
        digits.push_back(x % k);
        x /= k;
      }
      int i = 0;
      int j = digits.size() - 1;
      while (i < j) {
        if (digits[i++] != digits[j--]) {
          return false;
        }
      }
      return true;
    };

    i64 sum = 0LL;
    for (i64 start = 1; n > 0; start *= 10) {  // intervals of tenths
      // Generate odd-length palindromes first
      for (i64 i = start; n > 0 && i < start * 10; ++i) {
        i64 num = createPalindrome<true>(i);
        if (isKPalindrome(num)) {
          sum += num;
          --n;
        }
      }

      // Then generate even-length palindromes
      for (i64 i = start; n > 0 && i < start * 10; ++i) {
        i64 num = createPalindrome<false>(i);
        if (isKPalindrome(num)) {
          sum += num;
          --n;
        }
      }
    }
    return sum;
  }
};
