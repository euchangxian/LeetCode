#include <algorithm>
#include <vector>

using i64 = long long;

class Solution {
 public:
  i64 minOperations(std::vector<std::vector<int>>& queries) {
    // queries[i] = [l, r], defining an array of integers nums, consisting of
    // elements ranging from l to r inclusive. i.e., l,L+1,...r-1,r
    // In one operation:
    // - Select two integers a and b from the array,
    // - Replace them with floor(a/4), floor(b/4)
    // Determine the minimum number of operations required to reduce all
    // elements of the array to zero.
    // Return the sum of the results for all queries.
    //
    // First, note that floor(x/4 | x<=4) = 0. This means we only need 1 op
    // on x<=4. This is also equivalent to a shift-right-logical operator,
    // x >>= 2, removing the rightmost 2 bits, until we get 0.
    // Generalising, we can determine the number of operations required to
    // reduce each number: k = floor(log_4(x)) + 1, which is equivalent to
    // the distance of the first set bit from the right,
    // i.e.,ceiling{__builtin_ffs(x)/2}
    //
    // For each query, seems like we have to deal with even-odd length arrays.
    // Then, greedily operate on the largest elements first?
    // The number of set of pairs to perform operations on is ceil{(r-l+1)/2}
    // How to maffs this?
    // We can prefix sums.
    // Calculate number of operations from [1..r] - [1..l-1]
    constexpr auto prefixOps = [](int end) -> i64 {
      i64 result = 0;

      i64 operations = 1;
      int rangeStart = 1;
      while (rangeStart <= end) {
        // [rangeStart, rangeStart * 4 - 1]
        int rangeEnd = (rangeStart << 2) - 1;

        i64 rangeCount = std::min(rangeEnd, end) - rangeStart + 1;
        result += operations * rangeCount;

        ++operations;
        rangeStart <<= 2;
      }

      return result;
    };
    i64 result = 0;
    for (const auto& query : queries) {
      int left = query[0];
      int right = query[1];
      result += (prefixOps(right) - prefixOps(left - 1) + 1) / 2;
    }
    return result;
  }
};
