#include <algorithm>
#include <cstddef>
#include <vector>

using namespace std;
class Solution {
 private:
  // O(nlogn)
  std::vector<int> getLIS(const std::vector<int>& nums) {
    const size_t n = nums.size();

    // dp[i] represents the length of the longest increasing subsequence ENDING
    // at index i.
    std::vector<int> dp(n, 1);

    std::vector<int> subseq;
    subseq.reserve(n);
    subseq.push_back(nums[0]);

    for (size_t i = 1; i < n; ++i) {
      if (nums[i] > subseq.back()) {
        subseq.push_back(nums[i]);
      } else {
        // search for the first element in the subsequence that can be replaced
        auto it = std::lower_bound(subseq.begin(), subseq.end(), nums[i]);
        *it = nums[i];
      }

      dp[i] = subseq.size();
    }
    return dp;
  }

 public:
  int minimumMountainRemovals(vector<int>& nums) {
    // nums is a mountain array iff:
    // - nums.length >= 3 (input constraints 3 <= nums.length <= 1000)
    // - there exists some i in [0..n-1] such that
    //   - nums[0] < ... < nums[i-1] < nums[i] and
    //   - nums[i] > nums[i+1] > ... > nums[n-1]
    //
    // Remove k number of elements to make nums a mountain array, such that k
    // is a minimum.
    //
    // Input guarantees the existence of a mountain array.
    // Feels like a mix of Longest Increasing Subsequence and
    // Longest Decreasing Subsequence.
    // Then from these two, visualizing the graph, there should be a peak that
    // can be binary searched. This peak represents the index i in which both
    // LIS and LDS are maximised, indicating the number of elements in the
    // mountain array.
    // NOTE: Both of these functions are not monotonic. Neither are they
    // symmetrical. Therefore, a linear search would have to be done to find the
    // maximum LIS/LDS ending/starting at each index, so that we can minimize
    // the number of elements removed.
    const size_t n = nums.size();

    std::vector<int> lis = getLIS(nums);

    // Since we want mountain arrays, we don't want LDS ending at index i, but
    // the LDS STARTING at index i. To do that, we can reverse the input array,
    // the output array must also be reversed. Effectively reducing the problem
    // to an LIS.
    std::reverse(nums.begin(), nums.end());
    std::vector<int> lds = getLIS(nums);
    std::reverse(lds.begin(), lds.end());

    int maxMountainSize = 0;
    // Skip both first and last element.
    for (size_t i = 1; i < n - 1; ++i) {
      // Ensure that there is a corresponding increasing sequence before i,
      // and a decreasing sequence after i.
      if (lis[i] > 1 && lds[i] > 1) {
        // minus 1 to remove the double counting of index i.
        maxMountainSize = std::max(maxMountainSize, lis[i] + lds[i] - 1);
      }
    }

    return n - maxMountainSize;
  }
};
