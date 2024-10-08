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
  vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
    size_t const n = arr.size();

    vector<int> prefixXOR(n, 0);
    prefixXOR[0] = arr[0];
    for (int i = 1; i < n; ++i) {
      prefixXOR[i] = arr[i] ^ prefixXOR[i - 1];
    }

    size_t const m = queries.size();
    vector<int> answer(m, 0);
    for (int i = 0; i < m; ++i) {
      int const& start = queries[i][0];
      int const& end = queries[i][1];

      // queries include starting index
      answer[i] = prefixXOR[end] ^ prefixXOR[start] ^ arr[start];
    }

    return answer;
  }
};
