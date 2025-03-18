#include <algorithm>
#include <vector>

class Solution {
 public:
  int minDays(std::vector<int>& bloomDay, int m, int k) {
    if ((long long)m * (long long)k > bloomDay.size()) {
      return -1;
    }

    // The monotonic property is that as the number of days increase, the number
    // of flowers bloomed will increase
    int maximumDays = *std::max_element(bloomDay.begin(), bloomDay.end());

    int left = 0;
    int right = maximumDays;
    while (left < right) {
      int mid = left + (right - left) / 2;

      if (countBouquets(bloomDay, mid, k) < m) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }
    return left;
  }

 private:
  int countBouquets(const std::vector<int>& bloomDay,
                    int elapsed,
                    const int k) {
    int n = bloomDay.size();
    int bouquets = 0;  // Each bouquet must have k adjacent flowers

    int i = 0;
    while (i < n) {
      int adjacent = 0;
      while (i < n && bloomDay[i] - elapsed <= 0) {
        ++adjacent;
        ++i;
      }
      ++i;
      bouquets += (adjacent / k);
    }
    return bouquets;
  }
};
