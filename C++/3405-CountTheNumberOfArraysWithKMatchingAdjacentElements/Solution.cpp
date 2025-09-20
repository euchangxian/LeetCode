#include <array>
#include <ranges>
#include <tuple>
#include <utility>

using i64 = long long;
constexpr int MOD = 1E9 + 7;
constexpr int MAX_N = 1E5;
constexpr int MAX_M = 1E5;

i64 modPow(i64 base, i64 exp) {
  i64 result = 1LL;

  while (exp) {
    if (exp & 1) {
      result = (result * base) % MOD;
    }
    base = (base * base) % MOD;
    exp >>= 1;
  }
  return result;
}

i64 modInv(i64 n) {
  return modPow(n, MOD - 2);
}

auto [fact, factInv] = []() {
  std::array<i64, MAX_N> fact{};
  std::array<i64, MAX_N> factInv{};

  fact[0] = 1;
  for (int i = 1; i < MAX_N; ++i) {
    fact[i] = (fact[i - 1] * i) % MOD;
  }

  factInv[MAX_N - 1] = modInv(fact[MAX_N - 1]);
  for (int i = MAX_N - 1; i > 0; --i) {
    factInv[i - 1] = (factInv[i] * i) % MOD;
  }

  return std::make_pair(fact, factInv);
}();

i64 ncr(int n, int m) {
  return (((fact[n] * factInv[m]) % MOD) * factInv[n - m]) % MOD;
}

class Solution {
 public:
  int countGoodArrays(int n, int m, int k) {
    // Given three integers n, m, k. A good array of size n is defined as
    // follows:
    // - Each element in arr is in the inclusive range [1..m]
    // - Exactly k indices i (where 1 <= i < n) satisfy the condition
    //   arr[i-1] == arr[i]
    //
    // Think there should be a closed-form mathematical solution for
    // this too.
    // k=1 => two elements are equal to some value x.
    // k=2 => either three elements are equal to some value x,
    //        or two pairs of elements are equal to x and y respectively.
    // k=3 => either four elements are equal to x,
    //        three elements equal to x, two elements equal to y
    //        three pairs of elements equal to x, y and z respectively.
    //
    // Note the enumeration of choices: either make the new element equal to one
    // of the existing chains, or form a new chain.
    return (((ncr(n - 1, k) * m) % MOD) * modPow(m - 1, n - k - 1)) % MOD;
  }
};
