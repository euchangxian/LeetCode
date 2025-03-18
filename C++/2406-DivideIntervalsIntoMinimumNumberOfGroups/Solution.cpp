#include <algorithm>
#include <cstddef>
#include <queue>
#include <vector>

class Solution {
 public:
  int minGroups(std::vector<std::vector<int>>& intervals) {
    // Seems like finding the maximum number of intersections will suffice.
    // {5, 10}, {6, 8}, {1, 5}, {2, 3}, {1, 10}
    // {1, 5}, {1, 10}, {2, 3}, {5, 10}, {6, 8}
    // intersection between {1, 5}, {1, 10}, {2, 3} => 3 groups
    // intersection between {1, 10}, {5, 10}, {6, 8} => 3 groups
    //
    // Now the issue is to find the overlaps! Sorting is definitely necessary,
    // but sort by what? Starting?
    // The ending time also matters.
    // By using a min heap (with the earliest ending interval at the top),
    // we can iterate over the sorted intervals:
    //
    // If the current interval intersects with the earliest-ending interval,
    // then a separate group have to be allocated.
    // Otherwise, pop the top of the heap.
    // At the end, the size of the heap will be the number of groups.
    // With {1, 5}, {1, 10}, {2, 3}, {5, 10}, {6, 8},
    //
    // iter 0: heap: {}, push 5
    // iter 1: heap: {5}, {1, 10} intersects, push 10
    // iter 2: heap: {10, 5}, {2, 3} intersects, push 3
    // iter 3: heap: {10, 5, 3}, {5, 10} does not intersect. Pop 3, push 10.
    // iter 4: heap: {10, 10, 5}, {6, 8} does not intersect. Pop 5, push 8.
    sort(intervals.begin(), intervals.end(),
         [](const auto& a, const auto& b) { return a[0] < b[0]; });

    std::priority_queue<int, std::vector<int>, std::greater<>> ending;
    for (const auto& interval : intervals) {
      if (!ending.empty() && interval[0] > ending.top()) {
        ending.pop();  // no overlap
      }
      ending.push(interval[1]);
    }

    return ending.size();
  }
};
