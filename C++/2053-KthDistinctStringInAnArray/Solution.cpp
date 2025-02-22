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
  string kthDistinct(vector<string>& arr, int k) {
    if (k > arr.size()) {
      return "";
    }

    unordered_map<string, int> freq;
    for (string const& s : arr) {
      ++freq[s];
    }

    for (string const& s : arr) {
      if (freq[s] == 1 && --k == 0) {
        return s;
      }
    }
    return "";
  }
};
