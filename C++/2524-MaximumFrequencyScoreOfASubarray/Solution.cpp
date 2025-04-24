#include <algorithm>
#include <array>
#include <vector>

using i64 = long long;
constexpr int MOD = 1e9 + 7;
constexpr int MAX_VAL = 1e6;

int modPlus(int a, int b, int mod = MOD) {
  return (static_cast<i64>(a) + b) % mod;
}

int modMinus(int a, int b, int mod = MOD) {
  return ((static_cast<i64>(a) - b) + mod) % mod;
}

int modMult(int a, int b, int mod = MOD) {
  return (static_cast<i64>(a) * b) % mod;
}

// fastExp:
// if exponent is odd: result *= base
// base *= base;
// exp /= 2
int modPow(int base, int exp, int mod = MOD) {
  i64 result = 1;
  while (exp) {
    if (exp & 1) {
      result = modMult(result, base);
    }
    exp >>= 1;
    base = modMult(base, base);
  }

  return result;
}

int modInv(int a, int mod = MOD) {
  // prime mod only, using Fermat's little theorem.
  return modPow(a, mod - 2);
}

int modDiv(int a, int b, int mod = MOD) {
  return modMult(a, modInv(b));
}

class Solution {
 public:
  int maxFrequencyScore(std::vector<int>& nums, int k) {
    // The frequency score is the SUM of the distinct values in the subarray,
    // raised to the power of their FREQUENCIES, MODULO-ed.
    // Find the subarray of size k that has the largest score. Maximise the
    // value under MOD, not the actual value.
    //
    // Fixed-size sliding window of size k?
    // Finding and maintaining the frequency is simple.
    // Maintaining the sum is not so simple. Probably requires modulo
    // arithmetic.
    // Suppose we have sum = a^i + b^j.
    // Adding a new distinct character c is trivial: sum += c
    // Suppose we add a. Then, sum = a^(i+1) + b^j.
    // We could do sum -= a^i, then sum += a^(i+1). ModPow with fastExp is
    // potentially log(i) time though, which is acceptable in our case.
    const int n = nums.size();

    std::array<int, MAX_VAL + 1> freq{};
    int result = 0;
    int sum = 0;
    for (int r = 0; r < n; ++r) {
      // add rightmost of window
      int prevExp = freq[nums[r]]++;
      if (prevExp > 0) {
        int contribution = modPow(nums[r], prevExp);
        sum = modMinus(sum, contribution);

        contribution = modMult(contribution, nums[r]);
        sum = modPlus(sum, contribution);
      } else {
        sum = modPlus(sum, nums[r]);
      }

      // remove leftmost of window
      if (r >= k) {
        int nextExp = --freq[nums[r - k]];

        if (nextExp > 0) {
          int contribution = modPow(nums[r - k], nextExp + 1);
          sum = modMinus(sum, contribution);

          contribution = modDiv(contribution, nums[r - k]);
          sum = modPlus(sum, contribution);
        } else {
          sum = modMinus(sum, nums[r - k]);
        }
      }

      // if window is valid
      if (r >= k - 1) {
        result = std::max(result, sum);
      }
    }
    return result;
  }
};
