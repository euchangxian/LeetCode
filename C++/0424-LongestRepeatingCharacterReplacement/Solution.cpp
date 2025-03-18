#include <string>
#include <vector>

class Solution {
 public:
  int characterReplacement(std::string s, int k) {
    if (s.length() < 2) {
      return s.length();
    }

    int result = 0;
    std::vector<int> count = std::vector<int>(26, 0);
    int maxCount = 0;

    int l = 0;
    for (int r = 0; r < s.length(); ++r) {
      maxCount = std::max(maxCount, ++count[s[r] - 'A']);

      // If all k replacements have been used up, adjust the window
      // `r - l + 1 - maxCount` indicates the number of replacements used
      // where `r - l + 1` indicate the length of the window.
      while (r - l + 1 - maxCount > k) {
        --count[s[l++] - 'A'];  // some prefix/postfix addition fun here
        // Not necessary to find search for the maximum count.
        // maxCount = *max_element(count.begin(), count.end());
      }

      result = std::max(result, r - l + 1);
    }

    return result;
  }
};
