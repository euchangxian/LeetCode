#include <algorithm>
#include <utility>
#include <vector>

class Solution {
 public:
  int maximumGroups(std::vector<int>& grades) {
    const int n = grades.size();
    std::sort(grades.begin(), grades.end());

    int groups = 0;

    int prevSz = 0;
    int prevSum = 0;

    int currSz = 0;
    int currSum = 0;

    for (int i = 0; i < n; ++i) {
      ++currSz;
      currSum += grades[i];

      if (currSz > prevSz && currSum > prevSum) {
        ++groups;
        prevSz = std::exchange(currSz, 0);
        prevSum = std::exchange(currSum, 0);
      }
    }

    return groups;
  }
};
