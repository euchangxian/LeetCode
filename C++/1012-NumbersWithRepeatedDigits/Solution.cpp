#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdint>
#include <deque>
#include <functional>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

constexpr int DIGIT_LIMIT = 9;
constexpr int DIGITS = 10;

class Solution {
 public:
  int numDupDigitsAtMostN(
      int N) {  // Count number of positive integers in [1..n] that has at least
                // one repeated digit.
    //
    // Immediately feels like Inclusion-Exclusion.
    // I.e., Total number of Integers[1..n] - integers with NO repeated digits
    // Digit DP + bitmask?
    std::vector<int> digits;
    for (int x = N + 1; x > 0; x /= 10) {
      digits.push_back(x % 10);
    }

    int len = digits.size();
    int noDupWays = 9;
    int noDupDigits = noDupWays;
    for (int i = 1; i < len - 1; ++i) {
      noDupWays *= 10 - i;
      noDupDigits += noDupWays;
    }
  }

 private:
};
