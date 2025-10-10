#include <algorithm>
#include <limits>
#include <vector>

class Solution {
 public:
  int maximumEnergy(std::vector<int>& energy, int k) {
    // m magicians.
    // energy[i] = amount of energy that can be given/taken to/from you.
    // After absorbing energy from magician i, transported to (i+k) magician.
    // Repeated until the (i+k) magician does not exist.
    // Choose a starting point.
    // Return the maximum possible energy that can be gained.
    //
    // Is this not frog jump?
    // dp[i] = dp[i+k] + energy[i]
    const auto n = static_cast<int>(energy.size());

    int result = std::numeric_limits<int>::min();
    std::vector<int> dp(n);
    for (int i = n - 1; i >= 0; --i) {
      if (i + k < n) {
        dp[i] = dp[i + k] + energy[i];
      } else {
        dp[i] = energy[i];
      }
      result = std::max(result, dp[i]);
    }
    return result;
  }
};
