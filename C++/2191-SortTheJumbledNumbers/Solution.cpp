#include <algorithm>
#include <climits>
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
  vector<int> sortJumbled(vector<int> &mapping, vector<int> &nums) {
    unordered_map<int, int> mappedNumbers;
    for (int i = 0; i < nums.size(); ++i) {
      int mapped = 0;
      int exp = 0;

      int num = nums[i];
      if (num == 0) {
        // Handle edge case
        mappedNumbers[0] = mapping[0];
        continue;
      }
      while (num > 0) {
        int digit = num % 10;
        mapped += mapping[digit] * pow(10, exp++);

        num /= 10;
      }
      mappedNumbers[nums[i]] = mapped;
    }

    stable_sort(nums.begin(), nums.end(), [&mappedNumbers](int num1, int num2) {
      return mappedNumbers[num1] < mappedNumbers[num2];
    });
    return nums;
  }
};
