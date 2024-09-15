#include <algorithm>
#include <array>
#include <bitset>
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
  string largestNumber(vector<int> &nums) {
    sort(nums.begin(), nums.end(), [](int a, int b) {
      string candidate1 = to_string(a) + to_string(b);
      string candidate2 = to_string(b) + to_string(a);

      // compare the concantenation of the two strings in lexicographical
      // order and return the larger one first.
      return candidate1 > candidate2;
    });

    // Check for edge case where the first number is 0
    if (nums[0] == 0) {
      return "0";
    }
    string result;
    result.reserve(1024);
    for (int const &num : nums) {
      result += to_string(num);
    }

    return result;
  }
};
