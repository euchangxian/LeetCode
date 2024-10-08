#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
 private:
  int countBouquets(vector<int> const& bloomDay, int elapsed, int const k) {
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

 public:
  int minDays(vector<int>& bloomDay, int m, int k) {
    if ((long long)m * (long long)k > bloomDay.size()) {
      return -1;
    }

    // The monotonic property is that as the number of days increase, the number
    // of flowers bloomed will increase
    int maximumDays = *max_element(bloomDay.begin(), bloomDay.end());

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
};
