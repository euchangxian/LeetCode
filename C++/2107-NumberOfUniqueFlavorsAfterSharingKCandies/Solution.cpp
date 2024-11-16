#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  int shareCandies(std::vector<int>& candies, int k) {
    // candies[i] represent the flavors of ith candy.
    // give k consecutive candies, but want to keep as many unique flavors as
    // possible.
    // Seems like fixed-size sliding window of size k, where we want to minimize
    // the number of '1's in the window.
    //
    // Lol. misunderstand question.
    // but still, fixed-size sliding window of size k, where we want to maximize
    // duplicates / minimize unique flavors.
    // count the number of unique elements.
    //
    // Missed something again!
    // n - k where n is the total number of unique elements, k is the minimum
    // number of unique elements in the window is not entirely correct.
    // e.g., {1, 2, 2, 2,3}, k = 2
    // totalUnique = 3 (1, 2, 3)
    // minUnique = 1 (2, 2)
    // output: 3-1 = 2, but answer is actually 3.

    int totalUnique = 0;
    std::array<int, 100001> count{};
    for (int flavor : candies) {
      if (count[flavor]++ == 0) {
        ++totalUnique;
      }
    }
    if (k == 0) {
      return totalUnique;
    }

    // Keep track of the number of unique elements inside the window.
    // We want to minimize this.
    int windowUnique = 0;
    int maxUniqueOutside = 0;
    int l = 0;
    // {2, 4, 5}
    // total = 3
    // windowUnqiue = 1
    // r = 0, l = 0,
    for (int r = 0; r < candies.size(); ++r) {
      // we consider a flavor to be in the window, if there are no other same
      // flavors outside the window.
      if (--count[candies[r]] == 0) {
        ++windowUnique;
      }

      // if window has k elements, then update min, remove leftmost for next
      // iteration.
      // Hm. Doesnt handle edge case of k = 0.
      if (r - l + 1 >= k) {
        maxUniqueOutside =
            std::max(maxUniqueOutside, totalUnique - windowUnique);

        if (count[candies[l]]++ == 0) {
          // if the count increases beyond 0, then reintroduce a unique candy
          // outside the window.
          --windowUnique;
        }
        ++l;
      }
    }
    return maxUniqueOutside;
  }
};
