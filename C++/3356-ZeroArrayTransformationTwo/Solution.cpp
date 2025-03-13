#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  int minZeroArray(std::vector<int>& nums,
                   std::vector<std::vector<int>>& queries) {
    // queries[i] = [l, r, val], where nums[l] to nums[r] can be decremented
    // by [0..val], to make nums[i] = 0.
    // Determine the first k queries such that nums[i] == 0 for all i.
    //
    // Feels like Range Update. But a little hard to determine the minimum
    // number of queries; Best I can think of is O(n^2 logn)
    //
    // Line Sweep, determine the maximum decrement at each nums[i].
    // Nope. Does not maintain the order of the queries. Hmmmm.
    // Technically, given that we can sweep through nums instead, we can instead
    // maintain a pointer to queries, incrementing and processing it as
    // necessary to make the current index 0.
    const int n = nums.size();

    std::vector<int> difference(n + 1, 0);
    int sum = 0;
    int k = 0;
    for (int i = 0; i < n; ++i) {
      // cant zero-out
      while (sum + difference[i] < nums[i]) {
        if (k >= queries.size()) {
          return -1;
        }

        const auto& query = queries[k++];
        int l = query[0];
        int r = query[1];
        int val = query[2];

        // NOTE: we don't have to consider earlier indices; and also want to
        // be able to only check difference[i].
        // Only if this query range covers i.
        if (r >= i) {
          difference[std::max(l, i)] += val;
          difference[r + 1] -= val;
        }
      }

      sum += difference[i];
    }
    return k;
  }
};
