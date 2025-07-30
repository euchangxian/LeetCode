#include <array>
#include <bitset>
#include <string_view>

constexpr std::array VOWELS = {'a', 'e', 'i', 'o', 'u'};
constexpr std::bitset<26> IS_VOWEL = []() {
  std::bitset<26> isVowel;
  for (char c : VOWELS) {
    isVowel.set(c - 'a');
  }
  return isVowel;
}();

class Solution {
 public:
  bool isValid(std::string_view word) {
    // a word is valid if:
    // - minimum of 3 chars
    // - contains only digits and english letters (upper/lower)
    // - at least one vowel
    // - at least one consonant
    if (word.length() < 3) {
      return false;
    }

    bool hasVowel = false;
    bool hasConsonant = false;
    for (char c : word) {
      if (!std::isalnum(c)) {
        return false;
      }

      if (c >= '0' && c <= '9') {
        continue;
      }
      c = std::tolower(c);
      hasVowel |= IS_VOWEL[c - 'a'];
      hasConsonant |= !IS_VOWEL[c - 'a'];
    }
    return hasVowel && hasConsonant;
  }
};
