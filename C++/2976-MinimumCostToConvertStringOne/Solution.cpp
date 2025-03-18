#include <algorithm>
#include <climits>
#include <string>
#include <vector>

class Solution {
 public:
  long long minimumCost(std::string source,
                        std::string target,
                        std::vector<char>& original,
                        std::vector<char>& changed,
                        std::vector<int>& cost) {
    std::vector<std::vector<long long>> dist(
        26, std::vector<long long>(26, LLONG_MAX));
    for (int i = 0; i < 26; ++i) {
      dist[i][i] = 0;
    }

    for (int i = 0; i < original.size(); ++i) {
      int from = original[i] - 'a';
      int to = changed[i] - 'a';
      long long weight = cost[i];

      dist[from][to] = std::min(dist[from][to], weight);
    }

    for (int k = 0; k < 26; ++k) {
      for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
          if (dist[i][k] == LLONG_MAX || dist[k][j] == LLONG_MAX) {
            continue;
          }
          dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
        }
      }
    }

    long long result = 0;
    int n = source.length();
    for (int i = 0; i < n; ++i) {
      long long shortestDistance = dist[source[i] - 'a'][target[i] - 'a'];
      if (shortestDistance == LLONG_MAX) {
        return -1;
      }
      result += shortestDistance;
    }
    return result;
  }
};
