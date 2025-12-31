#include <vector>

class Solution {
 public:
  int dietPlanPerformance(std::vector<int>& calories,
                          int k,
                          int lower,
                          int upper) {
    // calories[i] on the ith day.
    // For every k consecutive days [calories[i]..calories[i+k-1]], determine T,
    // the total.
    // T < lower => lose 1 point
    // T > upper => gain 1 point
    // otherwise => no change
    // Return the number of points.
    const auto n = static_cast<int>(calories.size());
    auto signum = [&](int x) {
      if (x < lower) {
        return -1;
      }
      if (x > upper) {
        return 1;
      }
      return 0;
    };

    int result = 0;
    int T = 0;
    for (int i = 0; i < n; ++i) {
      T += calories[i];

      if (i >= k) {
        T -= calories[i - k];
      }

      if (i >= k - 1) {
        result += signum(T);
      }
    }
    return result;
  }
};
