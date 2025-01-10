#include <array>
#include <cstddef>
#include <cstdlib>
#include <string_view>

using i64 = long long;

constexpr std::size_t MAX_LEN = 10e4 + 1;
constexpr int BASE = 31;
constexpr int MOD = 1e9 + 7;

// Precompute Rolling Hash coefficients, since we want to add/remove the hashed
// character.
constexpr std::array<int, MAX_LEN> coeffs = []() -> std::array<int, MAX_LEN> {
  std::array<int, MAX_LEN> result;
  result[0] = 1;
  for (std::size_t i = 1; i < MAX_LEN; ++i) {
    result[i] = (1LL * BASE * result[i - 1]) % MOD;
  }
  return result;
}();

class Solution {
 public:
  int repeatedStringMatch(std::string_view a, std::string_view b) {
    // Find minimum number of times to repeat string a so that string b is a
    // substring.
    // Return -1 if impossible.
    //
    // Key insights:
    // 1. Need to handle edge cases where a single repeat isn't enough even when
    // len(a) > len(b)
    //    Example: a = "aba", b = "aa" requires 2 repeats
    // 2. Maximum repeats needed is ceiling(len(b)/len(a)) + 1
    //    - ceiling(len(b)/len(a)) covers the minimum length needed
    //    - +1 handles edge cases where pattern spans across boundary
    //
    // Time Complexity: O(L_a + L_b) where L_a = len(a), L_b = len(b)
    // - Uses Rabin-Karp with rolling hash for O(1) amortized substring checks
    // - Total string length processed is k*L_a where k = ceiling(L_b/L_a)
    // - k*L_a is bounded by L_b + L_a
    //
    // Space Complexity: O(1) - only stores fixed size coefficients array and
    // variables
    if (a == b) {
      return 1;
    }

    // ceiling division
    int k = (b.size() + a.size() - 1) / a.size();
    int patternHash = [&b]() {
      int hash = 0;
      for (int i = 0; i < b.size(); ++i) {
        hash = ((1LL * hash * BASE) + b[i] - 'a' + 1) % MOD;
      }
      return hash;
    }();

    if (rabinKarp(a, k, b, patternHash)) {
      return k;
    }

    if (rabinKarp(a, k + 1, b, patternHash)) {
      return k + 1;
    }

    return -1;
  }

 private:
  bool rabinKarp(std::string_view a,
                 int repeats,
                 std::string_view pattern,
                 int patternHash) {
    const int n = a.size();
    const int m = pattern.size();

    // the leftmost coefficient of the fixed-size window.
    const int leftCoeff = coeffs[m - 1];

    int hash = 0;
    for (int i = 0; i < n * repeats; ++i) {
      // remove leftmost of window if necessary
      // May cause negatives.
      // Essentially,
      // newHash = (currHash - coeff * leftChar)
      // newHash could be negative.
      // Thus, posHash = ((newHash % MOD) + MOD) % MOD
      // WARNING: The leftCoeff depends on the order of remove/add from/to the
      // window. Off-by-one!!!
      if (i >= m) {
        hash =
            (((hash - (1LL * leftCoeff * (a[(i - m) % n] - 'a' + 1))) % MOD) +
             MOD) %
            MOD;
      }

      // add right most of window.
      hash = ((1LL * hash * BASE) + a[i % n] - 'a' + 1) % MOD;

      if (hash == patternHash) {
        // Collisions are still theoretically possible, thus check the actual
        // substring match.
        // Since we avoided passing in k * a, a more complex indexing
        // is necessary.
        bool isEqual = [a, pattern, i, n, m]() -> bool {
          for (int idx = 0; idx < m; ++idx) {
            int aPos = (idx + (i - m + 1)) % n;

            if (a[aPos] != pattern[idx]) {
              return false;
            }
          }
          return true;
        }();

        if (isEqual) {
          return true;
        }
      }
    }

    return false;
  }
};
