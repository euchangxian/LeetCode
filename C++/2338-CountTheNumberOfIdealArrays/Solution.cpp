#include <algorithm>
#include <bitset>
#include <vector>

using i64 = long long;
constexpr int MOD = 1000000007;

constexpr int MAX_N = 1e4;
constexpr int MAX_LEN = 14;  // the longest is [1, 2, 4, ..., 2^13]

std::array<std::array<int, MAX_LEN + 1>, MAX_N + MAX_LEN + 1> choose = []() {
  // pascals triangle
  // dp[i][j] = dp[i-1][j] + dp[i-1][j-1]
  std::array<std::array<int, MAX_LEN + 1>, MAX_N + MAX_LEN + 1> dp{};
  dp[0][0] = 1;
  for (int i = 1; i < dp.size(); ++i) {
    dp[i][0] = 1;
    for (int j = 1; j <= std::min(i, MAX_LEN); ++j) {
      dp[i][j] = 1LL * (dp[i - 1][j] + dp[i - 1][j - 1]) % MOD;
    }
  }
  return dp;
}();

constexpr std::bitset<MAX_N + 1> isPrime = []() {
  std::bitset<MAX_N + 1> isPrime{};
  isPrime.flip();
  isPrime[0] = isPrime[1] = false;

  for (int i = 2; i <= MAX_N; ++i) {
    if (!isPrime[i]) {
      continue;
    }

    for (int j = i + i; j <= MAX_N; j += i) {
      isPrime[j] = false;
    }
  }
  return isPrime;
}();

std::vector<int> primes = []() {
  std::vector<int> primes;
  for (int i = 0; i <= MAX_N; ++i) {
    if (isPrime[i]) {
      primes.push_back(i);
    }
  }
  return primes;
}();

std::array<std::vector<int>, MAX_N + 1> factors = []() {
  std::array<std::vector<int>, MAX_N + 1> factors{};
  for (int i = 2; i <= MAX_N; ++i) {
    int x = i;
    for (int p : primes) {
      if (p * p > x) {
        break;
      }

      int count = 0;
      while (x % p == 0) {
        x /= p;
        ++count;
      }

      factors[i].push_back(count);
    }

    if (x > 1) {
      factors[i].push_back(1);
    }
  }
  return factors;
}();

class Solution {
 public:
  int idealArrays(int n, int maxValue) {
    // Given two integers which describes an ideal array.
    // An array arr of size n is ideal if:
    // 1. for every i in [0..n-1], 1 <= arr[i] <= maxValue.
    // 2. arr[i] % arr[i - 1] == 0 for every i in [1..n-1], i.e., divisible.
    // Want: Number of DISTINCT ideal arrays of length n.
    //
    // Is a construction problem. Hm.
    // Note that ideal arrays are non-decreasing.
    // Naively, choose a starting number from 1..maxValue. Count the number of
    // multiples of the starting number, i.e., for start=2, up till maxValue=20,
    // there are len([2, 4, ..., 20]) = 10 numbers.
    // Recursively, we can then set the next starting number.
    // Resembles a backtracking problem. However, given the input constraints
    // 2 <= n <= 10^4, 1 <= maxValue <= 10^4, an exponential time algorithm
    // will not suffice.
    //
    // Seems like some sort of DP, i.e., 2D DP where the states are n and val.
    // i.e., the repeated work is when val is chosen as the initial element
    // for a given n.
    // Counting is definitely involved though. I.e., given a sequence of
    // [2, 4, ..., 20], how many ways can we choose n numbers such that the
    // n numbers are non-decreasing.
    //
    // e.g., LIS = [1, 2, 3], n = 6, we can visualize this counting problem as
    // the number of ways to partition n = 6 => _ _ _ _ _ _
    // such that the series is non-decreasing.
    //
    // Also known as "stars and bars" combinatorics problem. Suppose
    // len(LIS) = k, then we will have k-1 bars, since we can divide
    // n into k distinct partitions, which looks like:
    // _ _ | _ _ | _ _ OR _ | _ _ _ | _ OR ...
    // 1 1 | 2 2 | 3 3    1 | 2 2 2 | 3
    // where we can place these k-1 bars into n-1 positions.
    // In essence, the result of this combinatorics is C(n-1, k-1).
    //
    // WARNING: (Wrong. When we do LIS/LID in the manner described below, we
    // lose information on the number of subsequences that have length at least
    // n.)
    // Therefore, first we find the longest increasing subsequence of each
    // i in 1..maxVal, that also fulfils the divisor property.
    // Then, for each of these subsequences, we can use combinatorics to derive
    // the total number of ideal arrays.
    // lisDp[i] represent the length of longest increasing divisible numbers
    // ending at val = i.
    i64 result = 0;
    for (int x = 1; x <= maxValue; ++x) {
      i64 count = 1;
      for (int k : factors[x]) {
        count = (count * choose[n - 1 + k][k]) % MOD;
      }

      result = (result + count) % MOD;
    }
    return result;
  }
};
