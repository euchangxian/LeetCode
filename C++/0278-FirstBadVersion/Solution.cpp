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
// The API isBadVersion is defined for you.
bool isBadVersion(int version);

class Solution {
 public:
  int firstBadVersion(int n) {
    // [1, 2, ..., n]. Find k such that
    // isBadVersion(k) == true => isBadVersion(k + 1) == true

    int left = 1;
    int right = n;
    while (left < right) {
      int mid = left + (right - left) / 2;

      if (!isBadVersion(mid)) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }
    return left;
  }
};
