#include <vector>

class Solution {
 public:
  int numOfSubarrays(std::vector<int>& arr, int k, int threshold) {
    // Return number of subarrays of size k and average GTE threshold.
    // Fixed sized sliding window, running average.

    int result = 0;
    int sum = 0;
    for (int i = 0; i < arr.size(); ++i) {
      sum += arr[i];

      if (i >= k) {
        sum -= arr[i - k];
      }

      if (i >= k - 1) {
        result += (sum / k) >= threshold;
      }
    }
    return result;
  }
};
