#include <algorithm>
#include <string_view>

class Solution {
 public:
  int minimumTime(std::string_view s) {
    // s[i] == 0 | 1,
    // 0 indicates OK,
    // 1 indicates ILLEGAL.
    // Want to remove all s[i] == 1 with the following operations:
    // - Remove from left with cost of 1
    // - Remove from right with cost of 1
    // - Remove from anywhere, with a cost of 2.
    // Return minimum cost.
    //
    // Hmm. For a prefix like "01...", always favour two left operations, since
    // it can only result in cheaper operations later on.
    // Similar for a suffix like "...10"
    //
    // The issue is when we have "001..."
    // The 2-cost operation is cheaper locally, but if the string looks like:
    // "00111...", then 3 * 2-cost operations = 6 is necessary, where if we
    // spent 2 to remove the prefix 0s, then we only need 3 1-cost operations to
    // remove the 1s, resulting in a lower cost of 5.
    //
    // Seems like prefix/suffix counting of 0s/1s. DP? Local != Global optimal
    // choice already kinda implies that.
    // But how to deal with being able to remove from both directions?
    //
    // Consider prefixes only, with only left and anywhere-operations.
    // At each index i:
    // - if s[i] == 0, then dp[i] = dp[i-1], no change.
    // - if s[i] == 1, then there are two choices:
    //   - remove with a cost-1 operation; this means everything before must
    //     have already been removed. cost = i+1
    //   - remove with a cost-2 operation; dp[i-1] + 2
    //   Thus, dp[i] = std::min(i+1, dp[i-1]+2).
    //
    // After determining the optimal cost to remove the prefix illegals,
    // when adding right-operations into consideration, i.e., removing right
    // with cost 1, we do not have to consider interleaving cost-1 and cost-2
    // operations on the right.
    //
    // Something like considering split points.
    const int n = s.size();

    int left = 0;
    int result = n;  // worst case, just do n 1-cost removals.
    for (int i = 0; i < n; ++i) {
      if (s[i] == '1') {
        left = std::min(left + 2, i + 1);
      }

      // left + suffix removals
      result = std::min(result, left + (n - 1 - i));
    }
    return result;
  }
};
