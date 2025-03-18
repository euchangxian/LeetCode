#include <unordered_map>
#include <vector>

class Solution {
 public:
  int findCenter(std::vector<std::vector<int>>& edges) {
    // The center must be contained in every edge, thus, it suffices to check
    // the first two edges
    if (edges[0][0] == edges[1][0] || edges[0][0] == edges[1][1]) {
      return edges[0][0];
    }
    return edges[0][1];
  }

  int findCenterSlow(std::vector<std::vector<int>>& edges) {
    std::unordered_map<int, int> freq;
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
