#include <cstddef>
#include <cstdlib>
#include <string_view>

class Solution {
 public:
  bool canMakeSubsequence(std::string_view s1, std::string_view s2) {
    // Operation:
    //   select a set of indices in str1, increment s1[i] to the next character
    //   cyclically.
    // Make s2 a subsequence of s1 by performing operation at MOST once.
    //
    // Since we want s2 to be a subsequence, s2 is the shorter string (or eq).
    // Therefore, we can iterate over s1.
    // If s1[i] is equal to s2[j], or can be made equal with a single cyclic
    // increment, then advance i and j.
    // Otherwise, advance i only.
    // if j is not at the end, then we cannot make the subsequence.
    if (s2.size() > s1.size()) {
      return false;
    }

    int j = 0;
    for (int i = 0; i < s1.size() && j < s2.size(); ++i) {
      char incr = (((s1[i] + 1) - 'a') % 26) + 'a';
      if (s1[i] == s2[j] || incr == s2[j]) {
        ++j;
      }
    }

    return j >= s2.size();
  }
};
