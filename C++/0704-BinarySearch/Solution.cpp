#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
public:
  int search(vector<int> &nums, int target) {
    int left = 0;
    int right = nums.size() - 1;

    // Invariant: if target exists, then target must be in nums[l:r] inclusive.
    while (left < right) {
      int mid = left + ((right - left) / 2);

      if (nums[mid] < target) {
        // target is to the right of mid.
        // Since we have already checked nums[mid], we can + 1.
        left = mid + 1;
      } else {
        right = mid;
      }
    }

    return nums[left] == target ? left : -1;
  }
};
