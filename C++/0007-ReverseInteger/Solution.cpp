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
  const int INT_MAX_THRESHOLD = INT_MAX / 10;
  const int INT_MIN_THRESHOLD = INT_MIN / 10;

public:
  int reverse(int x) {
    int result = 0;

    while (x) {
      if (result > INT_MAX_THRESHOLD || result < INT_MIN_THRESHOLD) {
        // Check if the next multiplication by 10 would result in overflow
        return 0;
      }

      result = (result * 10) + (x % 10); // shift left, add last digit
      x /= 10;
    }
    return result;
  }
};
