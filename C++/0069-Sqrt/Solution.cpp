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
public:
  int mySqrt(int x) {
    if (x == 0 || x == 1) {
      return x;
    }

    // if y * y == x, then sqrt(x) == y
    // Naively, do a linear search from 1 to x/2,
    // Find k such that k * k <= x
    // As such, we can find the maximal value of k using binary search
    int left = 1;
    int right = x / 2 + 1;
    while (left < right) {
      // Insight: typical questions find the minimum k such that
      // condition(k) == true => condition(k + 1) == true.
      // Here, we want to find the maximal k such that
      // condition(k) == true => condition(k + 1) == false.
      // While ceiling division can be used, another way is to rephrase
      // the target such that we are looking for the minimum k such
      // that condition(k) is false, and return k-1.
      int mid = left + (right - left) / 2;

      // if mid * mid <= x, condition(mid) is false, adjust left = left + 1
      if ((long long)mid * mid <= x) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }
    // we want maximal k instead of minimal k
    return left - 1;
  }
};
