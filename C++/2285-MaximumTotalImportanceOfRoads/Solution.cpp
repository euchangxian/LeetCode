#include <vector>

using namespace std;

class Solution {
private:
public:
  long long maximumImportance(int n, vector<vector<int>> &roads) {
    vector<int> frequencies = vector<int>(n, 0);
    for (auto const &edge : roads) {
      ++frequencies[edge[0]];
      ++frequencies[edge[1]];
    }

    sort(frequencies.begin(), frequencies.end());

    long long maximumScore = 0;
    for (int i = 0; i < n; ++i) {
      maximumScore += (long long)frequencies[i] * (long long)(i + 1);
    }
    return maximumScore;
  }
};
