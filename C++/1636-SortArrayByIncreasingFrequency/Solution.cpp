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
  vector<int> frequencySort(vector<int> &nums) {
    vector<int> frequencies(201, 0);
    for (int num : nums) {
      ++frequencies[num + 100];
    }
    sort(nums.rbegin(), nums.rend());

    stable_sort(nums.begin(), nums.end(), [&frequencies](int num1, int num2) {
      return frequencies[num1 + 100] < frequencies[num2 + 100];
    });

    return nums;
  }
};
