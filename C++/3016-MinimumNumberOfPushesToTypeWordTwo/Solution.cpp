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
  int minimumPushes(string word) {
    vector<int> frequencies(26, 0);
    for (char c : word) {
      ++frequencies[c - 'a'];
    }

    // Sort in Descending order of frequencies.
    // There is no need to store the mapping of characters to frequencies.
    sort(frequencies.rbegin(), frequencies.rend());

    // Greedily assign the mapping.
    // The highest 8 (2 to 9 button) frequencies will be assigned to have 1
    // button push The next 8 will be assigned to require 2 button pushes and so
    // on.
    int minPushes = 0;
    for (int i = 0; i < 26; ++i) {
      if (!frequencies[i]) {
        break;
      }

      minPushes += ((i / 8) + 1) * frequencies[i];
    }

    return minPushes;
  }
};
