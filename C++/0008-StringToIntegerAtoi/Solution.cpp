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
  int myAtoi(string s) {
    int i = 0;
    int n = s.length();

    // ignore leading whitespace
    while (i < n && s[i] == ' ') {
      ++i;
    }

    bool isPositive = true;
    if (s[i] == '-') {
      ++i;
      isPositive = false;
    } else if (s[i] == '+') {
      // skip this character
      ++i;
    }

    while (i < n && s[i] == '0') {
      ++i;
    }

    int result = 0;
    while (i < n && isdigit(s[i])) {
      int digit = s[i] - '0';
      if (result > INT_MAX / 10 ||
          (result == INT_MAX / 10 && digit > INT_MAX % 10)) {
        // The second condition is the tricky one for negative overflows.
        // E.g. current digit s[i] is '8', result is 2 147 483 64
        // If just checking for result < INT_MIN / 10, then potential overflow
        // will not be caught, since -2 147 483 64 >= INT_MIN/10 (-2 147 483 64)
        // Then, adding the last digit:
        // result = (2 147 483 64 * 10) + 8 = 2 147 483 648
        // will overflow, since it is larger than INT_MAX (2 147 483 647)
        return isPositive ? INT_MAX : INT_MIN;
      }
      result = (result * 10) + digit;
      ++i;
    }

    if (!isPositive) {
      return -result;
    }

    return result;
  }
};
