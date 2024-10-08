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
using ll = long long;
class Solution {
 private:
  ll mirrorLeftHalf(ll left, bool isOdd) {
    ll result = left;

    if (isOdd) {
      // the middle, or right-most of the left half do not need to be mirrored
      left /= 10;
    }
    while (left > 0) {
      // extract the right-most digit of the left half
      result = (result * 10) + (left % 10);
      left /= 10;
    }
    return result;
  }

 public:
  string nearestPalindromic(string n) {
    // 1 <= n.length <= 18: long long
    // Notice that by mirroring the first half of a number like 12322,
    // we can get the answer 12321
    // But for numbers like 139, mirroring the first half gives us 131,
    // where the answer is actually 141. As such, we need to increment
    // the first half "13" to "14", then mirror it
    // Similarly, for numbers like 131, mirroring gives us 131 (not valid)
    // or 141. But decrementing the first half "13" to "12" gives us 121
    // which is the correct answer.
    // Then, consider edge cases where n is close to numbers like 1000,
    // 10000, or small numbers like 11, 9.

    int halfIdx = (n.length() + 1) / 2;
    ll leftHalf = stoll(n.substr(0, halfIdx));
    bool isOdd = n.length() % 2;

    vector<ll> possibilities;
    possibilities.reserve(5);

    possibilities.push_back(mirrorLeftHalf(leftHalf, isOdd));
    possibilities.push_back(mirrorLeftHalf(leftHalf - 1, isOdd));
    possibilities.push_back(mirrorLeftHalf(leftHalf + 1, isOdd));

    // Handle edge cases like 999, 9999, 1001, 100001
    ll nines = pow(10, n.length() - 1) - 1;
    ll ones = pow(10, n.length()) + 1;
    possibilities.push_back(nines);
    possibilities.push_back(ones);

    ll num = stoll(n);
    ll minDiff = LLONG_MAX;
    ll result = LLONG_MAX;
    for (ll candidate : possibilities) {
      if (candidate == num) {
        continue;
      }

      ll currDiff = abs(num - candidate);
      if (currDiff < minDiff || (currDiff == minDiff && candidate < result)) {
        minDiff = currDiff;
        result = candidate;
      }
    }
    return to_string(result);
  }
};
