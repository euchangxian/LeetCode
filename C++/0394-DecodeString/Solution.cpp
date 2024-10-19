#include <cctype>
#include <cstddef>
#include <string>
#include <string_view>

using namespace std;
class Solution {
 private:
  string decode(string_view s, int& i) {
    // DFS
    string result;
    while (i < s.length() && s[i] != ']') {
      if (isalpha(s[i])) {
        result += s[i++];
        continue;
      }
      // A digit indicates a nested string to be decoded.
      int repeats = 0;
      while (i < s.length() && isdigit(s[i])) {
        repeats = (repeats * 10) + (s[i] - '0');
        ++i;
      }

      ++i;  // skip '[';
      string flattened = decode(s, i);
      ++i;  // skip ']'

      while (repeats--) {
        result += flattened;
      }
    }
    return result;
  }

 public:
  // Changing the signature to string_view is fine.
  string decodeString(string_view s) {
    // Seems similar to flattening a tree.
    int i = 0;
    return decode(s, i);
  }
};
