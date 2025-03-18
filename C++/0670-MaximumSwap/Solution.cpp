#include <algorithm>
#include <cstddef>
#include <string>

class Solution {
 public:
  int maximumSwap(int num) {
    // Swap two digits at most once to get the maximum value number.
    // At first glance, seems like a Greedy choice problem.
    // From the most significant digit, e.g., 8 in 8191, find the first
    // digit that is greater than 8 and swap => 9181.
    // The issue is that the digit that is greater may not exist?
    // e.g., 8181. Then the swap should happen between the next most significant
    // digit => 8811.
    // Also. It should not be the first digit that is greater. E.g., 8199.
    // 9189 is not greater than 9198.
    // Therefore, it needs to be the last digit.
    // Seems like a suffix max kinda thing.
    //
    // At the same time, seems like a monotonic non-decreasing stack where if
    // the window ends and the stack has at least 2 elements, then we can
    // swap the first and last element.
    //
    // The key problem is identifying the last AND largest digit from the back,
    // and the first, smaller digit that can be swapped with that digit.
    // Therefore, we can start iterating from the back.
    //
    // If we identify a larger digit, remember its idx (if swapping).
    // If we identify a digit smaller than the largest-so-far, store the
    // to-swap idx of the largest-so-far and this digit.
    // This is because there may be a more optimal pair to swap later on.
    // Therefore, smaller => update swapIdxs
    // Bigger => update largestIdx.
    //
    // At the end, swap the two idx.
    std::string numStr = std::to_string(num);
    const std::size_t n = numStr.length();

    int largestIdx = n - 1;
    int swapIdxGreater = largestIdx;
    int swapIdxSmaller = -1;
    for (int i = n - 2; i >= 0; --i) {
      if (numStr[i] == numStr[largestIdx]) {
        continue;
      }

      // If the current digit is strictly greater, memorize its idx.
      if (numStr[i] > numStr[largestIdx]) {
        // No need to '- 0'.
        largestIdx = i;
      } else {
        // Else, if strictly less than, update the swapIdx.
        // The largestIdx may have changed. Update it.
        swapIdxGreater = largestIdx;
        swapIdxSmaller = i;
      }
    }

    if (swapIdxSmaller == -1) {
      return num;  // no swaps.
    }
    std::swap(numStr[swapIdxGreater], numStr[swapIdxSmaller]);
    return std::stoi(numStr);
  }
};
