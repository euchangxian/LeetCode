#include <algorithm>
#include <vector>

class Solution {
 public:
  int maxScoreSightseeingPair(std::vector<int>& values) {
    // Score of a pair (i, j), i < j is values[i] + values[j] + i - j.
    // i.e., sum of values - distance.
    // Hmmm. We know for sure that as we iterate through j, the closest maximum
    // is more optimal. But its value decreases by 1 as we iterate.
    // Ooo. Similar to Kadane's
    int maxScore = 0;
    int maxVal = 0;

    for (int num : values) {
      maxScore = std::max(maxScore, maxVal + num - 1);
      maxVal = std::max(maxVal - 1, num);
    }

    return maxScore;
  }
};
