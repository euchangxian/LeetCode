#include <string>
#include <vector>

using namespace std;
class Solution {
public:
  int characterReplacement(string s, int k) {
    if (s.length() < 2) {
      return s.length();
    }

    int result = 0;
    vector<int> count = vector<int>(26, 0);
    int maxCount = 0;

    int l = 0;
    for (int r = 0; r < s.length(); ++r) {
      maxCount = max(maxCount, ++count[s[r] - 'A']);

      // If all k replacements have been used up, adjust the window
      // `r - l + 1 - maxCount` indicates the number of replacements used
      // where `r - l + 1` indicate the length of the window.
      while (r - l + 1 - maxCount > k) {
        --count[s[l++] - 'A']; // some prefix/postfix addition fun here
        // Not necessary to find search for the maximum count.
        // maxCount = *max_element(count.begin(), count.end());
      }

      result = max(result, r - l + 1);
    }

    return result;
  }
};
