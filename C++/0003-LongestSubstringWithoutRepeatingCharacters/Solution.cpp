#include <string>
#include <unordered_set>

using namespace std;
class Solution {
public:
  int lengthOfLongestSubstring(string s) {
    unordered_set<char> unique;
    int result = 0;

    int l = 0;
    for (int r = 0; r < s.length(); ++r) {
      while (unique.count(s[r])) {
        unique.erase(s[l++]);
      }
      unique.insert(s[r]);
      result = max(result, r - l + 1);
    }

    return result;
  }
};
