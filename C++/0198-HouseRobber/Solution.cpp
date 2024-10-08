#include <vector>

using namespace std;
class Solution {
 public:
  int rob(vector<int>& nums) {
    int currMax = 0;
    int prevMax = 0;

    for (int num : nums) {
      int newMax = max(currMax, prevMax + num);

      prevMax = currMax;
      currMax = newMax;
    }
    return currMax;
  }
};
