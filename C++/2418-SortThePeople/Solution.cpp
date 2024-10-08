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
 private:
 public:
  vector<string> sortPeople(vector<string>& names, vector<int>& heights) {
    vector<int> indices(names.size());
    for (int i = 0; i < names.size(); ++i) {
      indices[i] = i;
    }

    sort(indices.begin(), indices.end(),
         [&heights](int i, int j) { return heights[i] > heights[j]; });

    vector<string> result(names.size());
    for (int i = 0; i < names.size(); ++i) {
      result[i] = names[indices[i]];
    }

    return result;
  }
};
