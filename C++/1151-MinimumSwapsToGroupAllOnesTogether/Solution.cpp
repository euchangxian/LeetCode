#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  int minSwaps(std::vector<int>& data) {
    // Group all 1s in ANY place. Not to the left, not to the right. But ANY.
    // And the operations are SWAPs. Not shifts.
    // Hm. Let the number of 1s be K. Then, a fixed size sliding window, where
    // the minimum number of 0s in our window is our answer.
    // Can we do better than 2 passes?
    int k = std::count(data.begin(), data.end(), 1);

    int min = data.size();
    int zeroes = 0;
    for (int i = 0; i < data.size(); ++i) {
      zeroes += 1 - data[i];
      if (i >= k) {
        zeroes -= 1 - data[i - k];
      }

      // window-size condition
      if (i >= k - 1) {
        min = std::min(min, zeroes);
      }
    }
    return min;
  }
};
