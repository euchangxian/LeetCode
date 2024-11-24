#include <algorithm>
#include <climits>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  long long maxMatrixSum(std::vector<std::vector<int>>& matrix) {
    // Perform operation any number of times:
    // 1. Choose any two adjacent elements and multiply each of them by -1.
    // two elements are considered adjacent iff they share a border??
    // Maximize the total sum of the matrix elements.
    //
    // Okay one observation is that doing the flip twice is equivalent to
    // retaining the original number.
    //
    // Does Greedy approach work?
    // For each cell, consider all 4 cardinal directions. Flip the one that
    // results in the greatest increase in sum. I.e., (-ve, -ve), (-ve, +ve).
    // Doesnt seem right. The ideal strategy may be to flip a positive number
    // first, so that it can be flipped together with a negative number later.
    // e.g., [[1, 2, -3],
    //        [-4, 5, 6]]
    // Flip [1, 2]. Then flip [-1, -4] and [-2, -3].
    //
    // What about taking a more macro view of the Greedy approach?
    // It seems that as long as the number of negatives are even, it is always
    // possible to remove them, by "bubbling" the negative numbers towards each
    // other to eventually form a pair that can then be flipped.
    // Whereas for the odd case, we want to make the smallest absolute number
    // negative, and the rest positive.
    //
    // What about zero though? How does it affect our strategy? Flipping a zero
    // is still zero. So we probably do not want to count zeros?
    // Nope. We want to count zeros. This is because an odd number of negatives
    // can be made all positive by flipping with the zero.
    // i.e., if any zeros exist, the entire array can be made positive.
    // But in fact, this is already handled by maintaining the minimum absolute
    // number, which would be zero in this case.
    long long absSum = 0;  // absolute sum of values.
    int minAbs = INT_MAX;  // won't overflow, since 10^5 <= matrix[i][j]
    int negatives = 0;     // count of negatives
    for (auto& row : matrix) {
      for (int val : row) {
        if (val < 0) {
          ++negatives;
          val = -val;  // negate it for the next operations.
        }

        absSum += static_cast<long long>(val);
        minAbs = std::min(minAbs, val);
      }
    }

    if (negatives % 2 == 0) {
      // either a zero exists, or there are an even number of negatives in the
      // matrix. That means the whole matrix can be converted to positives.
      return absSum;
    }

    // Need to minus twice, because the absSum includes the minAbs.
    // We first remove the minAbs from the sum. Then minus the minAbs since it
    // is a negative.
    return absSum - minAbs - minAbs;
  }
};
