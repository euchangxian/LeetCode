#include <algorithm>
#include <cmath>
#include <vector>

class Solution {
 public:
  int minMoves(std::vector<int>& nums, int k) {
    // Given binary nums and k, in each operation:
    // - choose two adjacent indices and swap their values.
    // Minimum number of operations required such that nums has k consecutive 1s
    //
    // At first glance, seems like sliding window, i.e., smallest window that
    // has k '1's (not necessarily consecutive).
    // Then, it becomes median-finding to get the number of swaps within the
    // window, i.e., find the median '1', move all other '1's towards it, by
    // counting the number of positions from each other '1's.
    // Does this guarantee the minimum?
    //
    // Wait. LOL. We can reduce this to a fixed size sliding window of size k,
    // if we collect the indices of '1's.
    // Median is still correct, but the calculation of distances is not trivial.
    //
    // NOTE: tapped out
    // When we have positions of 1s at indices [p₀, p₁, ..., pₖ₋₁], we want to
    // make them consecutive by moving them to positions [x, x+1, ..., x+k-1]
    // for some starting position x (the median is to the right).
    // The total moves required would be:
    // |p₀-x| + |p₁-(x+1)| + |p₂-(x+2)| + ... + |pₖ₋₁-(x+k-1)|
    // This can be rewritten as:
    // |p₀-x| + |(p₁-1)-x| + |(p₂-2)-x| + ... + |(pₖ₋₁-(k-1))-x|
    // Thus, if we define a new array points, where:
    // - q₀ = p₀
    // - q₁ = p₁-1
    // - q₂ = p₂-2
    // - ...
    // - qₖ₋₁ = pₖ₋₁-(k-1)
    // Our problem becomes finding an x that minimizes:
    // |q₀-x| + |q₁-x| + |q₂-x| + ... + |qₖ₋₁-x|
    // It is trival that when x is the median, the sum of distance is minimized.
    std::vector<int> points;

    points.reserve(nums.size());
    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] == 1) {
        // compute qᵢ
        points.push_back(i - points.size());
      }
    }

    // initial window
    int dist = 0;
    int medianIdx = k / 2;
    for (int i = 0; i < k; ++i) {
      dist += std::abs(points[i] - points[medianIdx]);
    }

    int result = dist;
    for (int i = 1; i <= points.size() - k; ++i) {
      int nextMedianIdx = (k / 2) + i;

      // From  |q₀-x| + |q₁-x| + ... + |qₖ₋₁-x|
      // to    |q₁-y| + |q₂-y| + ... + |qₖ  -y|,
      // Thus (y-x) needs to be added to the left half, and
      // (y-x) need to be subtracted from the right half.
      // If K is ODD, then the net change is 0.
      // Otherwise, the net-change would be y-x, since we use floor division
      // to find the medians, and |right| - |left| == 1 => add y-x
      // NOTE: we take for granted without proof that we can arbitrarily choose
      // between two possible medians (when k is even). This is because the
      // optimal "meeting-point" should be one of the two '1's.
      // Take the trivial example {1, 0, 0, 0, 0, 0, 1}. Regardless of where
      // the meeeting point is set, the distance both '1's have to move will
      // sum up the same.
      if (k % 2 == 0) {
        dist += points[nextMedianIdx] - points[medianIdx];
      }

      // remove leftmost. No need std::abs
      dist -= points[medianIdx] - points[i - 1];

      // add rightmost of window
      dist += points[i + k - 1] - points[nextMedianIdx];

      medianIdx = nextMedianIdx;
      result = std::min(result, dist);
    }
    return result;
  }
};
