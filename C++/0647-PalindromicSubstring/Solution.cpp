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
  int expandCentre(string const& s, int l, int r) {
    int count = 0;
    while (l >= 0 && r < s.length() && s[l] == s[r]) {
      --l;
      ++r;
      ++count;
    }
    return count;
  }

 public:
  int countSubstrings(string s) {
    int n = s.length();

    int result = 0;
    for (int i = 0; i < n; ++i) {
      result += expandCentre(s, i, i);      // Count odd-length palindromes
      result += expandCentre(s, i, i + 1);  // Count even-length palindromes
    }
    return result;
  }
};
