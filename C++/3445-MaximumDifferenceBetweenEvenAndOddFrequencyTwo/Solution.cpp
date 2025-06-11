#include <algorithm>
#include <array>
#include <limits>
#include <string_view>
#include <vector>

class Solution {
 public:
  int maxDifference(std::string_view s, int k) {
    // Find the maximum difference between the frequency of two characters,
    // freq[a] - freq[b] in a substring sub of s, such that:
    // 1. subs.size >= k (at least k)
    // 2. freq[a] is odd
    // 3. freq[b] is even
    // Therefore, we want to maximise the odd freq, minimise the even freq.
    //
    // Note that s[i] = 0|1|2|3|4, i.e., 5 characters only.
    // Also, s.size <= 3*10^4,
    // Enumerate all substrings of at least size k? Sliding window like?
    // Nope, about O(n^3 * 5) naively.
    //
    // Given the small number of possible characters, can we solve a simpler
    // variant?
    // Hm. Even/Odd too. Prefix sums?
    // Hm. Suppose we obtain the prefix sums in O(N) time.
    // Then, enumerating all possible combinations take O(N^2) time, within
    // the constraints.
    //
    // NVM. Tapped out.
    // All pairs, sliding window for each pair.
    const int n = s.size();

    auto maxDiff = [&](char a, char b) -> int {
      int ans = std::numeric_limits<int>::min();
      std::vector<int> prefixA(n + 1);
      std::vector<int> prefixB(n + 1);
      for (int i = 1; i <= n; ++i) {
        prefixA[i] = prefixA[i - 1] + (s[i - 1] == a);
        prefixB[i] = prefixB[i - 1] + (s[i - 1] == b);
      }

      std::array<std::array<int, 2>, 2> best{
          {{std::numeric_limits<int>::min(), std::numeric_limits<int>::min()},
           {std::numeric_limits<int>::min(), std::numeric_limits<int>::min()}}};
      for (int i = k, j = 0; i <= n; ++i) {
        while (i - j >= k && prefixA[i] > prefixA[j] &&
               prefixB[i] > prefixB[j]) {
          int parityA = prefixA[j] & 1;
          int parityB = prefixB[j] & 1;
          int& b = best[parityA][parityB];
          b = std::max(b, prefixB[j] - prefixA[j]);
          ++j;
        }

        int parityA = prefixA[i] & 1;
        int parityB = prefixB[i] & 1;
        int validComb = best[1 - parityA][parityB];
        if (validComb != std::numeric_limits<int>::min()) {
          ans = std::max(ans, prefixA[i] - prefixB[i] + validComb);
        }
      }
      return ans;
    };

    int result = std::numeric_limits<int>::min();
    for (char a = '0'; a <= '4'; ++a) {
      for (char b = '0'; b <= '4'; ++b) {
        if (a == b) {
          continue;
        }

        result = std::max(result, maxDiff(a, b));
      }
    }
    return result == std::numeric_limits<int>::min() ? -1 : result;
  }
};
