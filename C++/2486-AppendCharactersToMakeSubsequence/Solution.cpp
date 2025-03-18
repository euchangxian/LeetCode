#include <string>

class Solution {
 public:
  // Returns the minimum number of characters that need to be appended to the
  // end of s so that t becomes a subsequence of s.
  // First intuition was that it was similar to Longest Common Subseqeuence.
  // I.e. if same character, then length + 1, different character, recurse on
  // two choices (two strings).
  // The difference here is that we only need to consider t as a subseqeuence of
  // s.
  int appendCharacters(std::string s, std::string t) {
    int ptrT = 0;
    for (int i = 0; i < s.size(); ++i) {
      if (s[i] == t[ptrT]) {
        ++ptrT;
      }
    }

    return t.size() - ptrT;
  }
};
