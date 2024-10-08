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
  int singleNumber(vector<int>& nums) {
    int single = 0;
    for (auto num : nums) {
      single ^= num;
    }
    return single;
  }
};
