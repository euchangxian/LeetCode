#include <algorithm>
#include <vector>

class Solution {
 public:
  int maxSatisfied(std::vector<int>& customers,
                   std::vector<int>& grumpy,
                   int k) {
    // store opened for n minutes.
    // n customers, customers[i] is the number of customers that enter the
    // store at the start of the ith minute, and leaves after the end of that
    // minute.
    // grumpy[i] = 1 indicates owner is grumpy during the ith minute, 0
    // otherwise.
    // If owner is grumpy, customers wont be satisifed
    // Using a single time: change the owner to not-grumpy for minutes
    // consecutive.
    // Return the maximum customers that can be satisfied.
    //
    // Seems like a mix between number of customers in a window, and the number
    // of grumpy minutes in the original.
    //
    // Get the original satisfied customers?
    // Then, sliding window?
    // any customers that were unsatisfied get added to a temp window.
    // Hm, no need two-pass.
    const auto n = static_cast<int>(customers.size());

    int original = 0;
    int windowMax = 0;
    int window = 0;
    for (int i = 0; i < n; ++i) {
      original += customers[i] * (1 - grumpy[i]);

      if (i >= k) {
        window -= customers[i - k] * grumpy[i - k];
      }
      window += customers[i] * grumpy[i];

      if (i + 1 >= k) {
        windowMax = std::max(windowMax, window);
      }
    }
    return original + windowMax;
  }
};
