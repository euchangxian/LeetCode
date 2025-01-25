#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iterator>
#include <ranges>
#include <vector>

class Solution {
 public:
  std::vector<int> lexicographicallySmallestArray(std::vector<int>& nums,
                                                  int limit) {
    // two (i, j) can be swapped if abs(nums[i] - nums[j]) <= limit
    // Perform operation any number of times and return the lexicographically
    // smallest array.
    // Observe that we can model each number as a node, and two numbers with
    // an edge if the differences are <= limit.
    // Thus, for each connected component, numbers within can be freely swapped.
    // Then, O(n) Union, O(nlogn) sort to greedily assign numbers.
    const int n = nums.size();

    std::vector<int> sorted = nums;
    std::sort(sorted.begin(), sorted.end());

    // We can partition the SORTED array, since consecutive elements will be
    // in the same group, if their differences are <= limit.
    auto chunks =
        sorted | std::ranges::views::chunk_by(
                     [limit](int a, int b) -> bool { return b - a <= limit; });

    // Then, for each of the partitioned chunks, we want an iterator, that will
    // allow us to "insert" in sorted order, i.e., take greedily the smallest
    // element of each group.
    // std::ranges::to is C++23.
    // Must be converted into a vector for random access.
    std::vector<std::vector<int>::iterator> groupIters =
        chunks | std::ranges::views::transform([](auto chunk) {
          return std::ranges::begin(chunk);
        }) |
        std::ranges::to<std::vector>();

    // MUST be converted into a vector for random access.
    std::vector<int> chunkLookup =
        chunks | std::ranges::views::transform([](auto chunk) -> int {
          return *std::ranges::rbegin(chunk);
        }) |
        std::ranges::to<std::vector>();

    for (int& num : nums) {
      // Notice that we can determine which group this number belongs to,
      // by binary searching the sorted array...
      // Given current number x, find first number t in the sorted array such
      // that x >= t.
      // upper_bound finds t such that x > t, while lower_bound finds the first
      // t such that x <= t
      // Therefore, in the above, we map the chunked array to the last number
      // in the group, so that we can use std::lower_bound, then std::distance
      // on the chunkLookup to determine the group.

      auto it = std::ranges::lower_bound(chunkLookup, num);
      int group = std::ranges::distance(std::ranges::begin(chunkLookup), it);

      auto& groupIt = groupIters[group];
      num = *groupIt;
      ++groupIt;
    }
    return nums;
  }
};
