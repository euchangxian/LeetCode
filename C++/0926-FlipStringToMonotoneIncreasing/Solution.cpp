#include <algorithm>
#include <cstddef>
#include <string_view>
#include <vector>

class Solution {
 public:
  int minFlipsMonoIncr(std::string_view s) {
    // count number of '1's after the last '0'?
    // count number of '0's after the first '1'?
    // Get the minimum i guess. Seems to be two-pass?
    // One pass to get the indices. Second pass to count.
    // Can we do better? Bit manipulation?
    // What about maintaining the count while tracking the indices?
    // DOES NOT WORK. Don't have to flip EITHER '1' or '0' only. Can flip both
    // in the optimal solution.
    // "10011111110010111011" => flip first '1' bit, then 4 of the back '0'
    // bits.
    //
    // This implies a decision tree, which implies DP!
    // What are the decisions though? What are the subproblems? How do we
    // determine that a string is monotonically increasing?
    // Decision is to flip a bit or not.
    //
    // Naively would be to explore each bit flip and check, with backtracking.
    // O(n * 2^n)
    //
    // DP[i] represents the minimum number of flip to convert s[:i] to a
    // monotonically increasing string?
    // Correct. Notice that traversing the string from left to right, seeing a
    // '1' is no issue, since appending a '1' to the end of a monotonically
    // increasing string is still monotonically increasing.
    // However, when we see a '0', we have to decide whether to flip this '0' to
    // a '1', or flip all '1's before this '0'.
    //
    // Can technically be done with O(1) space. O(n) solution is for
    // illustration.
    const std::size_t n = s.length();

    // dp[i] represents the min number of flips to convert s[:i]
    std::vector<int> dp(n + 1);
    dp[0] = 0;  // a substring of length 0 is vacously monotonically increasing.

    int ones = 0;
    for (std::size_t i = 1; i < n + 1; ++i) {
      if (s[i - 1] == '1') {
        ++ones;
        dp[i] = dp[i - 1];
        continue;
      }

      dp[i] = std::min(dp[i - 1] + 1, ones);
    }
    return dp[n];
  }
};
