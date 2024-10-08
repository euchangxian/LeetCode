#include <unordered_map>
#include <vector>

using namespace std;
class Solution {
 public:
  int findCenter(vector<vector<int>>& edges) {
    // The center must be contained in every edge, thus, it suffices to check
    // the first two edges
    if (edges[0][0] == edges[1][0] || edges[0][0] == edges[1][1]) {
      return edges[0][0];
    }
    return edges[0][1];
  }

  int findCenterSlow(vector<vector<int>>& edges) {
    unordered_map<int, int> freq;
    for (auto edge : edges) {
      ++freq[edge[0]];
      ++freq[edge[1]];
    }

    int n = freq.size();
    for (auto [key, value] : freq) {
      if (value == n - 1) {
        return key;
      }
    }

    return -1;
  }
};
