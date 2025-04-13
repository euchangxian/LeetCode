using i64 = long long;

constexpr int MOD = 1e9 + 7;
constexpr int PRIME_CHOICES = 4;
constexpr int EVEN_CHOICES = 5;

i64 modPow(int base, i64 exp, int mod = MOD) {
  i64 result = 1LL;
  i64 b = base;

  while (exp > 0) {
    if (exp & 1) {
      result = (result * b) % mod;
    }

    b = (b * b) % mod;
    exp >>= 1;
  }

  return result;
}

class Solution {
 public:
  int countGoodNumbers(i64 n) {
    // A digit string is Good if
    // - the digits at even indices are even, and
    // - the digits at odd indices are prime.
    // Total number of good digit strings of length n.
    // May contain leading zeros.
    // n <= 10^15 ????
    // Immediately rules out backtracking. Seems like a closed form solution.
    // Math?
    // i.e., number of even/odd positions. Then choices for each.
    // i.e., n = 4, E P E P
    //              5*4*5*4 = 400
    // Therefore, 5^e * 4^p total.
    // ModPow.
    i64 evenIndices = (n + 1) / 2;
    i64 oddIndices = n / 2;
    return static_cast<int>((modPow(EVEN_CHOICES, evenIndices) *
                             modPow(PRIME_CHOICES, oddIndices)) %
                            MOD);
  }
};
