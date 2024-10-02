#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cstdint>
#include <functional>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
public:
  vector<int> arrayRankTransform(vector<int> &arr) {
    set<int> nums(arr.begin(), arr.end());

    unordered_map<int, int> rank;
    int r{1};
    for (const int &num : nums) {
      rank[num] = r++;
    }

    for (size_t i{0}; i < arr.size(); ++i) {
      arr[i] = rank[arr[i]];
    }
    return arr;
  }
};
