#include <string>

class Solution {
 public:
  int countSubstrings(std::string s) {
    int n = s.length();

    int result = 0;
    for (int i = 0; i < n; ++i) {
      result += expandCentre(s, i, i);      // Count odd-length palindromes
      result += expandCentre(s, i, i + 1);  // Count even-length palindromes
    }
    return result;
  }

 private:
  int expandCentre(const std::string& s, int l, int r) {
    int count = 0;
    while (l >= 0 && r < s.length() && s[l] == s[r]) {
      --l;
      ++r;
      ++count;
    }
    return count;
  }
};
