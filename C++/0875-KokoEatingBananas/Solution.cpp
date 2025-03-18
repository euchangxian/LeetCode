#include <algorithm>
#include <vector>

class Solution {
 private:
  bool canFinishWithinHours(const std::vector<int>& piles,
                            int hours,
                            int rate) {
    int timeTaken = 0;
    for (int i = 0; i < piles.size(); ++i) {
      // Overflow-safe round-up for integer division
      timeTaken += 1 + ((piles[i] - 1) / rate);
    }
    return timeTaken <= hours;
  }

 public:
  int minEatingSpeed(std::vector<int>& piles, int h) {
    // Monotonic property that enables Binary Search is less obvious.
    // In this case, we are searching for the minimum value of k - eating rate
    // that allows us to consume the piles of banana within h hours.
    // The maximum possible eating rate will be max(piles), the minimum would
    // be 1.
    // Let the maximum rate be n.
    // Then, there will be a k in {1, n} such that for eating rates in
    // {1, k - 1}, Koko will not be able to finish the piles within h hours.
    // Then at {k, n}, Koko will be able to finish the piles.
    // As such, mapping the array of possible eating rate values to a boolean
    // that determines whether Koko can finish eating within h hours, it will
    // look like: {F, F, F, T, T, T, T, T}, where the first occurence of T
    // corresponds to k.
    int maxRate = *max_element(piles.begin(), piles.end());

    int left = 1;
    int right = maxRate;
    while (left < right) {
      int mid = left + (right - left) / 2;

      if (!canFinishWithinHours(piles, h, mid)) {
        left = mid + 1;
      } else {
        // There is a possibility that mid is the minimum, do not minus 1
        right = mid;
      }
    }

    return left;
  }
};
