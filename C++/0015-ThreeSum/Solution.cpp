#include <algorithm>
#include <vector>

using namespace std;
class Solution {
public:
  vector<vector<int>> threeSum(vector<int> &nums) {
    sort(nums.begin(), nums.end());

    vector<vector<int>> result;
    for (int i = 0; i < nums.size() - 2; ++i) {
      if (nums[i] > 0) {
        // Considering the way we only look forward for matches,
        // and the array is sorted, if the beginning number
        // is positive, we can terminate the algorithm because
        // there is no way to sum to zero.
        break;
      }

      if (i > 0 && nums[i] == nums[i - 1]) {
        // Considering the array is sorted, if the value
        // of the current is same as previous, then skip
        // duplicates.
        continue;
      }

      // reduce to 2-sum
      int target = -nums[i];

      int j = i + 1;
      int k = nums.size() - 1;
      while (j < k) {
        int sum = nums[j] + nums[k];
        if (sum < target) {
          ++j;
        } else if (sum > target) {
          --k;
        } else {
          result.push_back({nums[i], nums[j++], nums[k--]});

          while (j < k && nums[j] == nums[j - 1]) {
            ++j;
          }
          while (j < k && nums[k] == nums[k + 1]) {
            --k;
          }
        }
      }
    }
    return result;
  }
};
