#include <algorithm>
#include <vector>

class Solution {
 private:
 public:
  long long maximumImportance(int n, std::vector<std::vector<int>>& roads) {
    std::vector<int> frequencies = std::vector<int>(n, 0);
    for (const auto& edge : roads) {
      ++frequencies[edge[0]];
      ++frequencies[edge[1]];
    }

    std::sort(frequencies.begin(), frequencies.end());

    long long maximumScore = 0;
    for (int i = 0; i < n; ++i) {
      maximumScore += (long long)frequencies[i] * (long long)(i + 1);
    }
    return maximumScore;
  }
};
