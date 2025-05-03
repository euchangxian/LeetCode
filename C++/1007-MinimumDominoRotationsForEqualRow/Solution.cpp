#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdint>
#include <deque>
#include <functional>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

constexpr int INF = 1E9;
class Solution {
 public:
  int minDominoRotations(std::vector<int>& tops, std::vector<int>& bottoms) {
    // tops[i]/bottoms[i] = [1..6]
    // Return the minimum number of operations to make either tops all equal,
    // or bottoms all equal.
    // Each operation: swap tops[i] and bottoms[i].
    //
    // Hmmm. One observation is that both tops and bottoms are symmetrical.
    // Thus, WLOG, if we can make tops all equal to x with K operations, then
    // we can make bottoms all equal to x with N-K operations.
    // Ah. This is not completely correct. Consider:
    // {1, 1, 2, 2}
    // {2, 1, 1, 1}
    // To make tops all-equal, 2 operations are needed. But < 2 = 1 operation
    // is needed to make bottoms all equal.
    //
    // The next observation is that at the i-th column,
    // WLOG, if bottoms[i] != tops[i-1], then it is no longer possible to make
    // tops all-equal.
    //
    // Hm. Third is there is only 2 possible candidates to make tops/bottoms
    // equal to: tops[0] or bottoms[0].
    // Therefore, two choices for each tops/bottoms?
    //
    // Consider a constrained variant: Make either tops or bottoms all-equal
    // to tops[0].
    // Then, we can easily calculate the number of operations for tops/bottoms.
    // Maintain kTops, kBottoms. At each index i, there are multiple cases.
    // - if tops[i] == tops[0], kTop is unchanged
    // - if bottoms[i] == tops[0], kBottoms is unchanged
    // - Otherwise:
    //   - if bottoms[i] == tops[0], then kTops += 1
    //     - else, kTops is not possible
    //   - if tops[i] == tops[0], then kBottoms += 1
    //     - else, kBottoms is not possible.
    // It seems that unless for each column, both values are equal to tops[0],
    // we can eliminate from consideration one row.
    const int n = tops.size();

    auto minRotations = [&](int target) {
      int kTops = 0;
      int kBottoms = 0;
      for (int i = 0; i < n; ++i) {
        if (tops[i] != target) {
          if (bottoms[i] == target) {
            ++kTops;
          } else {
            kTops = INF;
          }
        }

        if (bottoms[i] != target) {
          if (tops[i] == target) {
            ++kBottoms;
          } else {
            kBottoms = INF;
          }
        }
      }
      return std::min(kTops, kBottoms);
    };

    // Ahhh. If both tops[0] and bottoms[0] can be made, then the number of
    // swaps for both will be equal (consider each column).
    // Thus, if tops[0] can be made, then we only need to check once.
    if (int result = minRotations(tops[0]); result < INF) {
      return result;
    }
    if (int result = minRotations(bottoms[0]); result < INF) {
      return result;
    }
    return -1;
  }
};
