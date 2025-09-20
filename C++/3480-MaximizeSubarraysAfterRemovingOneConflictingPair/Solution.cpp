#include <algorithm>
#include <utility>
#include <vector>

using i64 = long long;

class Solution {
 public:
  i64 maxSubarrays(int n, std::vector<std::vector<int>>& conflictingPairs) {
    // Given sorted nums = [1..n], and
    // conflictingPairs[i] = [a, b] indicating that a and b are conflicting.
    // Remove exactly one conflicting pair.
    // Count the number of non-empty subarrays of nums which do not contain
    // any conflicting pairs.
    // Return the maximum of such subarrays.
    //
    // There are n^2 non-empty subarrays.
    // Given that nums is sorted from 1 to n, we want to remove a pair such that
    // the difference between a and b is maximized.
    //
    // Seems like an interval question.
    // Reframing it, we can see it as removing an interval such that the
    // total size of ranges without any intervals in it is maximized.
    // Removing the largest interval is not necessarily the most optimal, since
    // the number of subarrays is quadratic to the length.
    //
    // But looking at another perspective, given that the intervals are all
    // overlapping, we want to remove the interval will result in the most-empty
    // subarray, i.e., the largest and least overlapping.
    std::vector<std::vector<int>> right(n + 1);
    for (const auto& pair : conflictingPairs) {
      right[std::max(pair[0], pair[1])].push_back(std::min(pair[0], pair[1]));
    }

    i64 result = 0LL;

    // right-most and 2nd right-most index as at i
    i64 rightmost = 0LL;
    i64 rightmost2 = 0LL;

    // gain[a] number of subarrays gained from removing a
    std::vector<i64> gain(n + 1, 0LL);

    for (int r = 1; r <= n; ++r) {
      for (int lVal : right[r]) {
        if (lVal > rightmost) {
          rightmost2 = std::exchange(rightmost, lVal);
        } else if (lVal > rightmost2) {
          rightmost2 = lVal;
        }
      }

      result += r - rightmost;

      if (rightmost > 0) {
        gain[rightmost] += rightmost - rightmost2;
      }
    }

    i64 maxGain = *std::max_element(gain.begin(), gain.end());
    return result + maxGain;
  }
};
