#include <cstddef>
#include <queue>
#include <vector>

using namespace std;
class Solution {
 public:
  vector<int> smallestRange(vector<vector<int>>& nums) {
    // nums[i] is sorted in non-decreasing order.
    // Breaking down to just two arrays, e.g.,
    // {4, 10, 15, 24, 26} and
    // {0, 9, 12, 20}
    // the sorted property can be exploited to find the minimum range.
    // Iterating from the start, with indices i, j = 0:
    // range = {nums[0][i], nums[1][j]} = {4, 0} (length = 4)
    //
    // Advancing pointer i would make no sense, as 4 is already greater than 0,
    // and given the sorted property, would only increase the length of the
    // range.
    // Thus, we can make a greedy choice here to advance the lower-value ptr.
    //
    // i = 0, j = 1 => range = {4, 9} (length = 5)
    // i = 1, j = 1 => range = {10, 9} (length = 1) *Minimum
    // i = 1, j = 2 => range = {10, 12} (length = 2)
    // i = 2, j = 2 => range = {15, 12} (length = 3)
    // i = 2, j = 3 => range = {15, 20} (length = 5)
    // i = 3, j = 3 => range = {24, 20} (length = 4)
    // Since j is at the end, we can terminate the loop.
    //
    // The issue here is how to generalize this algorithm to k lists.
    // {4, 10, 15, 24, 26},
    // {0, 9, 12, 20},
    // {5, 18, 22, 30}
    //
    // From intuition, attempting to generalize to 3 pointers:
    // iter 1: consider 4, 0, 5. Pick {0, 5}
    // iter 2: consider 4, 9, 5. Pick {4, 9}
    // iter 3: consider 10, 9, 5. Pick {5, 10}
    // iter 4: consider 10, 9, 18. Pick {9, 18}
    // iter 5: consider 10, 12, 18. Pick {10, 18}
    // iter 6: consider 15, 12, 18. Pick {12, 18}
    // iter 7: consider 15, 20, 18. Pick {15, 20}
    // iter 8: consider 24, 20, 18. Pick {18, 24}
    // iter 9: consider 24, 20, 22. Pick {20, 24}
    // terminate.
    //
    // Can be seen that the number of elements in consideration increases
    // linearly with k. The gist of it is to pick the smallest and largest
    // element in the list of elements in consideration, and advance the
    // pointer to the smallest element.
    // But it seems that having k pointers is not feasible? Unless an array is
    // defined to keep track.
    //
    // Which data-structure allows efficient min/max lookup?
    // An ordered Set seems to fit our requirements.
    // However, it does not seem necessary to lookup the max value every
    // iteration. It will only change if the next element after incrementing
    // the minimum element ptr is greater.
    const size_t k = nums.size();

    vector<size_t> ptrs(k, 0);

    // {value, numsIdx}. Allows us to know which ptr to increment
    priority_queue<pair<int, size_t>, vector<pair<int, size_t>>, greater<>>
        minHeap;
    int maxVal = INT_MIN;
    for (size_t i = 0; i < k; ++i) {
      minHeap.emplace(nums[i][0], i);
      maxVal = max(maxVal, nums[i][0]);
    }

    vector<int> result{0, INT_MAX};
    while (minHeap.size() == k) {
      const auto [minVal, minPtr] = minHeap.top();
      minHeap.pop();

      // If the range is smaller
      if (maxVal - minVal < result[1] - result[0] ||
          ((maxVal - minVal == result[1] - result[0]) && minVal < result[0])) {
        result = {minVal, maxVal};
      }

      // increment the pointer of the minVal and insert
      if (++ptrs[minPtr] < nums[minPtr].size()) {
        const int nextElem = nums[minPtr][ptrs[minPtr]];

        minHeap.emplace(nextElem, minPtr);
        maxVal = max(maxVal, nextElem);
      }
    }

    return result;
  }
};
