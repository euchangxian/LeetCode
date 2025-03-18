#include <climits>
#include <string>
#include <unordered_map>

class Solution {
 public:
  std::string minWindow(std::string s, std::string t) {
    if (s.length() < t.length()) {
      return "";
    }

    int counter = 0;
    std::unordered_map<char, int> frequencies;
    for (char c : t) {
      ++frequencies[c];
      ++counter;
    }

    int minLeft = 0;
    int minLength = INT_MAX;

    int l = 0;
    for (int r = 0; r < s.length(); ++r) {
      if (!frequencies.count(s[r])) {
        continue;
      }

      if (frequencies[s[r]] > 0) {
        --counter;
      }
      --frequencies[s[r]];

      while (counter == 0) {
        if (r - l + 1 < minLength) {
          minLeft = l;
          minLength = r - l + 1;
        }
        if (frequencies.count(s[l])) {
          if (++frequencies[s[l]] > 0) {
            ++counter;
          }
        }
        ++l;
      }
    }

    if (minLength == INT_MAX) {
      return "";
    }

    return s.substr(minLeft, minLength);
  }
};
