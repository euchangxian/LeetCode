#include <climits>
#include <cstdlib>
#include <string>
#include <vector>

class Solution {
 public:
  int equalSubstring(std::string s, std::string t, int maxCost) {
    int n = s.length();
    std::vector<int> costs = std::vector<int>(n);
    for (int i = 0; i < n; ++i) {
      costs[i] = abs(s[i] - t[i]);
    }

    int left = 0;
    int maxWindowSize = INT_MIN;
    int budgetUsed = 0;
    for (int right = 0; right < n; ++right) {
      budgetUsed += costs[right];
      while (budgetUsed > maxCost) {
        budgetUsed -= costs[left];
        ++left;
      }
      maxWindowSize = std::max(maxWindowSize, right - left + 1);
    }
    if (maxWindowSize == INT_MIN) {
      return 0;
    }
    return maxWindowSize;
  }
};
