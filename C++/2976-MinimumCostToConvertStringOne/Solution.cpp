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
  long long minimumCost(string source, string target, vector<char> &original,
                        vector<char> &changed, vector<int> &cost) {
    vector<vector<long long>> dist(26, vector<long long>(26, LONG_LONG_MAX));
    for (int i = 0; i < 26; ++i) {
      dist[i][i] = 0;
    }

    for (int i = 0; i < original.size(); ++i) {
      int from = original[i] - 'a';
      int to = changed[i] - 'a';
      long long weight = cost[i];

      dist[from][to] = min(dist[from][to], weight);
    }

    for (int k = 0; k < 26; ++k) {
      for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
          if (dist[i][k] == LONG_LONG_MAX || dist[k][j] == LONG_LONG_MAX) {
            continue;
          }
          dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        }
      }
    }

    long long result = 0;
    int n = source.length();
    for (int i = 0; i < n; ++i) {
      long long shortestDistance = dist[source[i] - 'a'][target[i] - 'a'];
      if (shortestDistance == LONG_LONG_MAX) {
        return -1;
      }
      result += shortestDistance;
    }
    return result;
  }
};
