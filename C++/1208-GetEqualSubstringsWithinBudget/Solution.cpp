#include <climits>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Solution {
 public:
  int equalSubstring(string s, string t, int maxCost) {
    int n = s.length();
    vector<int> costs = vector<int>(n);
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
      maxWindowSize = max(maxWindowSize, right - left + 1);
    }
    if (maxWindowSize == INT_MIN) {
      return 0;
    }
    return maxWindowSize;
  }
};

int main() {
  cout << Solution().equalSubstring("abcd", "bcdf", 3) << endl;
  cout << Solution().equalSubstring("abcd", "cdef", 3) << endl;
  cout << Solution().equalSubstring("abcd", "acde", 0) << endl;
}
