#include <algorithm>
#include <array>
#include <bitset>
#include <string_view>

constexpr int NUM_CHARS = 128;
constexpr std::string_view vowels{"aeiou"};
constexpr std::bitset<NUM_CHARS> isVowel = []() {
  std::bitset<NUM_CHARS> result;
  for (char c : vowels) {
    result.set(c);
  }
  return result;
}();

class Solution {
 public:
  int maxFreqSum(std::string_view s) {
    // Find vowel with maximum frequency.
    // Find consonant with maximum frequency.
    // Return the sum.
    std::array<int, NUM_CHARS> freq{};
    int maxVowel = 0;
    int maxConsonant = 0;
    for (char c : s) {
      ++freq[c];
      if (isVowel[c]) {
        maxVowel = std::max(maxVowel, freq[c]);
      } else {
        maxConsonant = std::max(maxConsonant, freq[c]);
      }
    }

    return maxVowel + maxConsonant;
  }
};
