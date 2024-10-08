#include <string>
#include <vector>

using namespace std;

class Solution {
 public:
  string longestCommonPrefix(vector<string>& strs) {
    if (strs.empty()) {
      return "";
    }

    string prefix = strs[0];
    for (int i = 1; i < strs.size(); ++i) {
      int j = 0;
      while (j < min(prefix.size(), strs[i].size()) &&
             prefix[j] == strs[i][j]) {
        ++j;
      }
      prefix = prefix.substr(0, j);  // Adjust the prefix
      if (prefix.empty()) {
        break;  // Early exit if there's no common prefix
      }
    }
    return prefix;
  }
};
