#include <array>
#include <cstddef>
#include <cstdlib>

constexpr int MOD{1'000'000'007};
using i64 = long long;

class Solution {
 public:
  int countGoodStrings(int low, int high, int zero, int one) {
    // At each step, perform either of the following
    // - append '0' `zero` times,
    // - append '1' `one` times.
    // A good string has length between low and high inclusive.
    // Count number of different good strings.
    // Seems math-y! i.e., the actual character appended does not matter.
    // Find the minimum length in the range [low, high], the maximum length in
    // the range [low, high]. Then should already be able to count? Not sure
    // about the formula though!
    // Naively, can be done with DFS + backtracking, where count(...) returns 1
    // if length is in the range [low..high].
    // count(low,high,zero,one,length) = count(low,high,zero,one,length+zero)
    //                                  +count(low,high,zero,one,length+one)
    // Can be memoized, I guess?
    // dp[i] = number of substrings with length i.
    // dp[i] = dp[i-zero] + dp[i-one]
    // Then, sum up dp[low] to dp[high]?
    if (one < zero) {
      // ensure zero < one.
      return countGoodStrings(low, high, one, zero);
    }

    i64 count = 0;
    std::array<i64, 100'001> dp{};
    dp[zero] += 1;
    dp[one] += 1;

    for (int i = zero; i <= high; ++i) {
      dp[i] = (dp[i] + dp[i - zero]) % MOD;

      if (i >= one) {
        dp[i] = (dp[i] + dp[i - one]) % MOD;
      }

      if (i >= low) {
        count = (count + dp[i]) % MOD;
      }
    }
    return count;
  }
};
