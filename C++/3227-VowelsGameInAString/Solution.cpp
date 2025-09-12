#include <algorithm>
#include <array>
#include <bitset>
#include <string_view>

constexpr std::array vowels = {'a', 'e', 'i', 'o', 'u'};
constexpr std::bitset<255> isVowel = []() {
  std::bitset<255> result;
  for (char c : vowels) {
    result[c] = 1;
  }
  return result;
}();

class Solution {
 public:
  bool doesAliceWin(std::string_view s) {
    // Given string s, Alice and Bob take turns playing, Alice starts first.
    // - Alice -> remove any non-empty substring from s that contains an odd
    //   number of vowels.
    // - Bob -> remove any non-empty substring from s that contains an even
    //   number of vowels.
    // First player that cannot make a move loses.
    //
    // Seems like counting segments of vowels to get something like:
    // [1, 2, 1, 2] representing a|ee|i|oo.
    //
    // What is the optimal play? On Alice's turn, remove odd number of vowels
    // from even segments to reduce the available segments for Bob.
    // Given that odd-even => odd, Bob can only extend his "lifespan" but can
    // not reduce Alice's plays by removing from Odd Segments.
    // Thus, we can reduce it further: Bob cannot make a move if there are no
    // remaining segments left, or the remaining segments are odd.
    //
    // Even number of even-sized segments => Alice wins, by reducing the first
    // segment picked to 1, ensuring she maintains a last-move that Bob can not
    // touch.
    // Odd number of even-sized segments => Alice wins?
    //
    // As long as there is a single vowel, Alice wins?
    return std::ranges::any_of(s, [](char c) { return isVowel[c]; });
  }
};
