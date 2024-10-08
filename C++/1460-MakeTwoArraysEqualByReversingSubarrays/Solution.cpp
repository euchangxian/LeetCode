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
  // Reversing a subarray of size two is equivalent to swapping adjacent
  // elements. Since there can be any number of steps, the array can be made
  // equal to the target if they have the same elements.
  bool canBeEqual(vector<int>& target, vector<int>& arr) {
    vector<int> freq(1001, 0);

    for (int const& num : target) {
      ++freq[num];
    }

    int count = target.size();
    for (int const& num : arr) {
      if (freq[num]) {
        --freq[num];
        --count;
      }
    }
    return count == 0;
  }
};
