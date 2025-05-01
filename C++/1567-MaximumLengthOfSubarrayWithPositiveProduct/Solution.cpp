#include <algorithm>
#include <utility>
#include <vector>

class Solution {
 public:
  int getMaxLen(std::vector<int>& nums) {
    // length of positive/negative product subarrays
    int positive = 0;
    int negative = 0;
    int result = 0;

    // wew. Consider appending a number x.
    // If x is negative, then adding to a positive product subarray will change
    // it into negative and vice-versa.
    for (int x : nums) {
      if (x == 0) {
        positive = negative = 0;
      }

      if (x > 0) {
        ++positive;

        // adding to an already-negative product subarray will extend it.
        if (negative > 0) {
          ++negative;
        }
      }

      if (x < 0) {
        // swap(positive,negative)
        // Then, for the negative subarray, it will be equal to the old length
        // of the positive subarray, with x appended to it.
        // For the positive, consider the previously-negative subarray.
        // If the length was > 0, then adding x will flip the product, and we
        // can add 1.
        positive = std::exchange(negative, positive + 1);

        if (positive > 0) {
          ++positive;
        }
      }

      result = std::max(result, positive);
    }
    return result;
  }

  int getMaxLenNaive(std::vector<int>& nums) {
    // Return maximum length of a subarray where the product of all its elements
    // is positive.
    // -1E9 <= nums[i] <= 1E9
    //
    // Sliding window seems intuitive, but notice that we can not shrink the
    // window if the product becomes negative. A subsequent nums[i] may turn
    // the product positive again.
    // Also, notice that we do not need the actual magnitude of nums[i], just
    // -ve or +ve.
    // Ah. Also, a positive product means > 0.
    // A subarray containing even number of negative numbers, and NO 0s is
    // valid.
    //
    // We can split into subarrays by 0s.
    // If the subarray has even, then trivial.
    // If odd, we need to split the subarray. How? Remove the first or last
    // negative.
    //
    // Thus, we only need to keep track of the length of the subarray
    // considered, l, r, the number of negatives, and the first and last
    // negatives index.
    const int n = nums.size();
    auto bestSplit = [](int l, int r, int negatives, int leftNeg,
                        int rightNeg) {
      const int n = r - l;
      if (negatives % 2 == 0) {
        return n;
      }

      int exclPref = r - (leftNeg + 1);
      int exclSuff = rightNeg - l;
      return std::max(exclPref, exclSuff);
    };

    int l = 0;
    int negatives = 0;
    int leftNeg = -1, rightNeg = -1;
    int maxLength = 0;
    for (int r = 0; r < n; ++r) {
      if (nums[r] < 0) {
        ++negatives;
        if (leftNeg == -1) {
          leftNeg = r;
        }
        rightNeg = r;
      }

      if (nums[r] == 0) {
        // update maxLength
        maxLength =
            std::max(maxLength, bestSplit(l, r, negatives, leftNeg, rightNeg));

        l = r + 1;
        negatives = 0;
        leftNeg = rightNeg = -1;
      }
    }

    maxLength =
        std::max(maxLength, bestSplit(l, n, negatives, leftNeg, rightNeg));
    return maxLength;
  }
};
