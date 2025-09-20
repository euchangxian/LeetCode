#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <numeric>
#include <vector>

using i64 = long long;
class Solution {
 public:
  i64 kSum(std::vector<int>& nums, int k) {
    // Choose any subsequence and take its sum.
    // Define the K-Sum of the array as the kth largest subsequence sum that
    // can be obtained (not necessarily distinct).
    //
    // First thought was that the subsequence requirement is useless, since we
    // only want to pick and choose elements.
    // The array could contain negatives.
    // A naive method would be to sort the array.
    // The sum of positives would be the 1st largest. Then, either adding a
    // negative, or removing a positive would result in the second largest.
    // And so on.
    //
    // Determining which to choose is probably a two-pointer approach, where
    // the left pointer starts at the beginning of the array, which will be
    // the negatives, and the right pointer starts at the first positive
    // element.
    //
    // Thus, O(nlogn + k)
    // Can we do better?
    // O(n) sum all positives.
    // Then we can do O(nk) quickselects, or O(nlogk) partial-sort to pick the
    // k smallest elements (using a custom comparator to take the absolutes)
    // Therefore, dominated by O(nlogk) term, which is faster.
    // Wait. Not exactly. The sequence can be alternating, i.e.,
    // 2nd largest: include -1 => sum - 1
    // 3rd largest: exclude 2 => sum - 2
    // 4th largest: include -1, exclude 2 =>  sum - 3
    // i.e., There are two choices to each element: included/not-included.
    // Guess this is where the complexity comes from...
    //
    // Regardless, still seems like sorting is necessary, though by absolute
    // value instead.
    i64 sum = std::reduce(
        nums.begin(), nums.end(), 0LL,
        [](i64 acc, int val) -> i64 { return acc + std::max(0, val); });
    return sum;
  }
};
