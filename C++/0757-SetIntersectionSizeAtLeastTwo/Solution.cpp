#include <algorithm>
#include <limits>
#include <ranges>
#include <utility>
#include <vector>

class Solution {
 public:
  int intersectionSizeTwo(std::vector<std::vector<int>>& intervals) {
    // intervals[i] = [start, end], representing all integers from start to
    // end inclusive.
    // A containining set is an array nums where each interval from from
    // intervals has at least two integers in nums.
    // Return the minimum possible size of a containing set.
    const auto n = static_cast<int>(intervals.size());

    // sort by descending end, tiebreak by ascending start.
    std::ranges::sort(intervals, [](const auto& x, const auto& y) {
      if (x[1] == y[1]) {
        return x[0] > y[0];
      }
      return x[1] < y[1];
    });

    int result = 0;
    int largest = std::numeric_limits<int>::min();
    int secondLargest = std::numeric_limits<int>::min();
    for (auto [start, end] :
         intervals | std::views::transform([](const auto& interval) {
           return std::make_pair(interval[0], interval[1]);
         })) {
      auto isIncludedInLargest = start <= largest;
      auto isIncludedInSecondLargest = start <= secondLargest;

      if (isIncludedInLargest && isIncludedInSecondLargest) {
        continue;
      }

      result += isIncludedInLargest ? 1 : 2;
      secondLargest = isIncludedInLargest ? largest : end - 1;
      largest = end;
    }

    return result;
  }
};
