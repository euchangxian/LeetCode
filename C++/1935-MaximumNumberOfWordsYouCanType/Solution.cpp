#include <bitset>
#include <string_view>

constexpr int NUM_CHARS = 128;

class Solution {
 public:
  int canBeTypedWords(std::string_view text, std::string_view brokenLetters) {
    // Keyboard with brokenLetters keys.
    // Return the number of words in text that can be typed with this keyboard.
    // WORDS. i.e., space-delimited.
    std::bitset<NUM_CHARS> broken;
    for (char c : brokenLetters) {
      broken.set(c);
    }

    int result = 0;
    bool possible = true;
    for (char c : text) {
      if (c == ' ') {
        result += possible;
        possible = true;
      } else {
        possible &= !broken[c];
      }
    }
    return result + possible;
  }
};
