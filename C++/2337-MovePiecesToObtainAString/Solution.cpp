#include <cstddef>
#include <cstdlib>
#include <string_view>

class Solution {
 public:
  bool canChange(std::string_view s, std::string_view t) {
    // given strings where s[i] = L | R | _, indicating which direction
    // it can move. A piece can only move into a Blank Space _.
    // Return true if target can be obtained from moving characters any number
    // of times.
    // Seems like counting problem. Prefix/Suffix-ish.
    // But also need to take into account the position.
    // i.e., at any index i, WLOG, if any of the prefix/suffix 'R' are to the
    // right of the target position, then we can never create the Target.
    //
    // But wouldnt this already be handled by counting at '_'?
    // Hm. Seems like counting the SUFFIX 'L', and the PREFIX 'R' would solve
    // this.
    // Since SUFFIX 'L's indicate the number of 'L's that can (POSSIBLY) be
    // moved to the left, while PREFIX 'R's indicate 'R's that can (POSSIBLY)
    // move to the right.
    // Prefix/Suffix including the current element. This is to count characters
    // already at its correct position.
    //
    // Hm. The target prefix/suffix count should only be at the positions with
    // characters.
    // HMMMM. We only need to check RELATIVE positions. Thus, when a non '_'
    // character is encountered, we need to check BOTH s[i] and t[j], whether
    // they are equal, simplifying things massively.
    // To handle the case where a 'L'/'R' character is to the Left/Right of
    // its expected position, when we encounter them:
    // for 'L': check i >= j indicating the L character can move left.
    // for 'R': check i <= j.
    const std::size_t n = s.size();

    int i = 0;
    int j = 0;
    while (i < n && j < n) {
      // Skip non-significant characters.
      while (i < n && s[i] == '_') {
        ++i;
      }
      while (j < n && t[j] == '_') {
        ++j;
      }

      if (i >= n || j >= n) {
        break;
      }

      // check relative
      if (s[i] != t[j]) {
        return false;
      }

      // check move-ability
      if (s[i] == 'L' && i < j) {
        return false;
      }

      if (s[i] == 'R' && i > j) {
        return false;
      }

      ++i;
      ++j;
    }

    while (i < n && s[i] == '_') {
      ++i;
    }
    while (j < n && t[j] == '_') {
      ++j;
    }

    // both should be matching at the end
    return i == n && j == n;
  }
};
