#include <cstddef>
#include <cstdlib>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;
class Solution {
 public:
  bool containsNearbyDuplicate(vector<int>& nums, int k) {
    // No constance space constraint.
    // -10^9 <= nums[i] <= 10^9 => Prolly use an unordered_map instead of an
    // array.
    // Since we are traversing left-to-right, i.e., the indices will be in
    // sorted order, we just need to maintain the last-seen idx of each unique
    // number.
    std::unordered_map<int, int> prevIdx;
    for (int i = 0; i < nums.size(); ++i) {
      auto iter = prevIdx.find(nums[i]);
      if (iter == prevIdx.end()) {
        prevIdx[nums[i]] = i;
        continue;
      }
      // Otherwise, there was a duplicate, check distance
      if (std::abs(iter->second - i) <= k) {
        return true;
      }

      // otherwise, update the last seen
      iter->second = i;
    }
    // if we reach here, there is no matching pair of numbers
    return false;
  }
};
