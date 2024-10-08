#include <unordered_map>
#include <vector>

using namespace std;
class Solution {
 public:
  vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> indexOf;
    for (int i = 0; i < nums.size(); ++i) {
      int goal = target - nums[i];
      if (indexOf.count(goal)) {
        return {indexOf[goal], i};
      }

      indexOf[nums[i]] = i;
    }

    // Guaranteed to have a solution. will not reach here.
    return {};
  }
};
