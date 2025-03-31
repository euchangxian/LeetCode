#include <algorithm>
#include <vector>

using i64 = long long;
class Solution {
 public:
  i64 putMarbles(std::vector<int>& weights, int k) {
    // Divide into K subarrays such that:
    // - No subarrays is empty
    // - The cost of each subarray [l..r] is weights[l] + weights[j]
    // The total score is the sum of costs of all k subarrays.
    // Return the difference between the maximum and minimum scores.
    //
    // Okok. Simplify the problem first. Suppose we want to find the maximum
    // score.
    // Naively, pick the top k-1 elements such that they are in their own
    // partition.
    // Cant really guarantee that the remaining elements are contiguous.
    //
    // First, notice that nums[0] and nums[n-1] are always in the sum.
    // This allow us to reduce the problem elegantly to one where we look for
    // "cuts".
    // Specifically, k-1 cuts, where suppose we make a "cut" at index i,
    // then nums[i] will be part of the left subarray, while nums[i+1] will be
    // part of the right subarray.
    // Thus, we can add nums[i] + nums[i+1] to our sum.
    // Let A[j] = nums[i]+nums[i+1] for all j in [0..n-2].
    // Then, our problem is simplified to picking the k-1 largest A[j].
    // O(nlogn)
    // Then, to get the smallest sum, we can simply pick the k-1 smallest sum.
    //
    // NOTE: Interesting. What an interesting insight.
    // Notice that we only need the top/bottom k-1 elements. We do not need
    // these k-1 elements to be sorted.
    // Thus, we can do QuickSelect to place all these elements in the first k
    // slots in an unspecified order.
    // O(n).
    if (k == 1 || k == weights.size()) {
      return 0;  // only one way to partition.
    }

    for (int i = 0; i < weights.size() - 1; ++i) {
      weights[i] += weights[i + 1];
    }

    weights.pop_back();

    i64 diff = 0;

    // place the k-1 smallest element in the first k-1 slots.
    std::nth_element(weights.begin(), weights.begin() + k - 1, weights.end());
    for (int i = 0; i < k - 1; ++i) {
      diff -= weights[i];  // min sum
    }

    // place the k-1 largest element at the last k-1 slots
    std::nth_element(weights.begin(), weights.begin() + weights.size() - k + 1,
                     weights.end());
    for (int i = 0; i < k - 1; ++i) {
      // no underflow risk. handled the case where k == weights.size() above.
      diff += weights[weights.size() - 1 - i];  // max sum
    }
    return diff;
  }
};
