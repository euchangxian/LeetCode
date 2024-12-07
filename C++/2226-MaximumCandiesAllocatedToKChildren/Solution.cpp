#include <algorithm>
#include <climits>
#include <cstddef>
#include <cstdlib>
#include <span>
#include <utility>
#include <vector>

class Solution {
  using i64 = long long;

 private:
  bool feasible(std::span<const int> candies, i64 k, int maxCandy) {
    i64 count = 0;
    for (int pile : candies) {
      count += pile / maxCandy;
    }
    return count >= k;
  }

 public:
  int maximumCandies(std::vector<int>& candies, long long k) {
    // Notice that piles cannot be merged, and each children can only take at
    // most one pile.
    // Thus, the maximum number of candies allocated to each child is
    // monotonically non-increasing.
    // A greedy approach splitting the largest pile evenly will not work.
    //
    // Binary searching the max would probably work though. i.e., let C be the
    // candies allocated to each of the k child.
    // Though, input constraints candies[i] <= 10^7, k <= 10^12?

    int left = 1;
    auto [sum,
          right] = [](std::span<const int> candies) -> std::pair<i64, int> {
      i64 sum = 0;
      int max = INT_MIN;
      for (int candy : candies) {
        sum += candy;
        max = std::max(max, candy);
      }
      return {sum, max};
    }(candies);

    if (k > sum) {
      return 0;
    }

    while (left < right) {
      // ceiling div.
      int mid = left + (right - left + 1) / 2;

      if (feasible(candies, k, mid)) {
        // we can get a better max
        left = mid;
      } else {
        right = mid - 1;
      }
    }

    return left;
  }
};
