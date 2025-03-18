#include <string_view>
#include <unordered_set>

class Solution {
 public:
  int lengthOfLongestSubstring(std::string_view s) {
    std::unordered_set<char> unique;
    int result = 0;

    int l = 0;
    for (int r = 0; r < s.length(); ++r) {
      while (unique.count(s[r])) {
        unique.erase(s[l++]);
      }
      unique.insert(s[r]);
      result = std::max(result, r - l + 1);
    }

    return result;
  }
};
