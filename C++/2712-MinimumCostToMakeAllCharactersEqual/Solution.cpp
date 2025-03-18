#include <algorithm>
#include <cstddef>
#include <string_view>
#include <vector>

class Solution {
 public:
  long long minimumCost(std::string_view s) {
    // First glance seems like DP, since decisions at each s[:i] is necessary.
    // How to assign values to the decisions? What are the subproblems?
    // Lets start from base case:
    // substring of length 0 => no flips
    // length 1 => no flips (all equal already)
    // length 2 => hm, either flip the previous i bits with a cost of i + 1?
    //            or keep this bit? Or flip the current bit to the nth bit.
    //
    // NOTE: Only need to consider flipping if the current and previous bits are
    // not equal.
    //
    // Okay. Note the difference in terminology. To be clear here, invert will
    // mean either of the two operations we have: invert 0 to ith bit with cost
    // of i, or invert i to nth bit with cost of n - i.
    // Flip will mean flipping '0' to '1' or '1' to '0'.
    //
    // The key insight here is that the number of FLIPs required to make the
    // binary string uniform will always remain the same, regardless of the
    // permutation/INVERSION of the string, "010" or "101".
    //
    // As such, we do not need to care about the composition of the string.
    // We just care about adjacent bits. If the adjacent bits are different,
    // then we have to make a choice: To flip the prefix with cost i, or to flip
    // the suffix with cost n-i.
    // E.g.,: "0 1 0"
    //         ^[i=1]
    // 1. Make everything before it match it: "1 1 0" (cost = i = 1)
    // 2. Make it match everything before it: "0 0 0" (cost = n-i = 2)
    //
    // Thus, notice that there is a Greedy Choice here, as we are only
    // interested in local comparisons (still quite a big logical jump).
    // A Greedy choice asserts that picking the locally optimal choice is
    // sufficient to reach the globally optimal result (i.e., one of the
    // possible outcomes can be formed from a Greedy Choice).
    //.
    // Proof (by contradiction):
    //  1. Suppose for the sake of contradiction that there exists a better
    //     solution that doesn't always choose the minimum cost at each
    //     differing position (s[i] != s[i-1]).
    //  2. Then, there must exist some position i where:
    //     2.1. s[i] != s[i-1]
    //     2.2. The optimal solution chooses the more expensive inversion
    //          (e.g., cost n-i when i < n-i)
    //  3. Consider the effect of inversions:
    //     3.1. When a range is inverted, all bits in that range flip
    //     3.2. The relationships between adjacent bits WITHIN the inverted
    //          range remain unchanged
    //     3.3. Only the boundaries of the inversion affect whether adjacent
    //          bits match or differ
    //  4. Therefore:
    //     4.1. Any differences at positions > i must still be resolved
    //     4.2. The cost to resolve these future differences remains the same
    //          regardless of which inversion we chose at position i
    //     4.3. This contradicts our assumption that choosing the more expensive
    //          inversion at position i could lead to a better overall solution
    //  5. Thus, the greedy choice of picking min(i, n-i) at each position where
    //     s[i] ≠ s[i-1] must be optimal.
    const std::size_t n = s.length();

    // Again, can be done with constant space.
    std::vector<long long> dp(n, 0);
    for (std::size_t i = 1; i < n; ++i) {
      dp[i] = dp[i - 1];

      if (s[i] != s[i - 1]) {
        dp[i] += std::min(i, n - i);
      }
    }

    return dp[n - 1];
  }
};
