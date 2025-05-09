#include <array>
#include <string_view>
#include <vector>

using i64 = long long;
constexpr int MOD = 1E9 + 7;
constexpr int MAX_N = 80;

constexpr int modPow(i64 base, int exp) {
  i64 result = 1;
  while (exp) {
    if (exp & 1) {
      result = (result * base) % MOD;
    }
    base = (base * base) % MOD;
    exp >>= 1;
  }
  return result;
}

constexpr std::array<int, MAX_N + 1> factMod = []() {
  std::array<int, MAX_N + 1> fact{};
  fact[0] = fact[1] = 1;
  for (int i = 2; i <= MAX_N; ++i) {
    fact[i] = (1LL * i * fact[i - 1]) % MOD;
  }
  return fact;
}();

constexpr std::array<int, MAX_N + 1> factModInv = []() {
  std::array<int, MAX_N + 1> factInv{};
  factInv[0] = factInv[1] = 1;
  for (int i = 2; i <= MAX_N; ++i) {
    factInv[i] = modPow(factMod[i], MOD - 2);
  }
  return factInv;
}();

class Solution {
 public:
  int countBalancedPermutations(std::string_view num) {
    // A string of digits is balanced if the sum of digits at even indices is
    // equal to the sum of the digits at odd indices.
    // Return the number of distinct permutations of num that are balanced.
    //
    // Counting the total sum of digits, we can reduce this to a knapsack-like
    // question, where we count the number of ways we can get total/2 sum at
    // even AND odd indices.
    // Nope. Not exactly. Some digits can only be used once.
    // Though, expanding on this train of thought, WLOG, we can count the number
    // of ways to make sum S at even indices using k digits.
    // Then, the remaining n-k digits must be placed at the odd indices, and
    // their sum must be equal to S, though this can be derived using total-S
    //
    // First, if an arrangement is valid, then that arrangement can be permuted
    // within even and within odd indices.
    // Note that we need to handle duplicates too.
    // i.e., n!/#duplicates
    // Though, given that we have modulo, we need modInverse...
    //
    // Hm. Then how do we ensure uniqueness?
    // The frequency array can be used.
    //
    // Hm. Naively, with the above observations, we have two choices:
    // - WLOG, Place at even indices
    // - Skip (i.e., place at odd indices)
    // Then, we have number of ways to make up (sum, #chars)
    // Hm. We need to keep track of the frequency table too.
    const int n = num.size();
    int total = 0;
    std::array<int, 10> freq{};
    for (char c : num) {
      ++freq[c - '0'];
      total += c - '0';
    }
    if (total & 1) {
      return 0;  // not possible if odd total.
    }

    const int target = total / 2;
    int evens = n / 2;  // number of even indices
    int unrestricted = (1LL * factMod[evens] * factMod[n - evens]) % MOD;

    // memo[d][sum][used] represent the number of ways to make sum using used
    std::vector<std::vector<std::vector<int>>> memo(
        10, std::vector<std::vector<int>>(evens + 1,
                                          std::vector<int>(target + 1, -1)));
    auto dfs = [&](this auto&& dfs, int d, int used, int sum) {
      if (d >= 10) {
        if (used == evens && sum == target) {
          return unrestricted;
        }
        return 0;
      }

      // prune
      if (used > evens || sum > target) {
        return 0;
      }

      int& ans = memo[d][used][sum];
      if (ans != -1) {
        return ans;
      }

      ans = 0;
      for (int x = 0; x <= freq[d]; ++x) {
        // promote
        i64 takeX = dfs(d + 1, used + x, sum + (x * d));

        takeX = (takeX * factModInv[x]) % MOD;
        takeX = (takeX * factModInv[freq[d] - x]) % MOD;
        ans = (ans + takeX) % MOD;
      }
      return ans;
    };

    return dfs(0, 0, 0);
  }
};
