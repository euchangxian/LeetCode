#include <array>
#include <bitset>
#include <string>
#include <string_view>

constexpr std::array<char, 10> vowels{
    {'A', 'E', 'I', 'O', 'U', 'a', 'e', 'i', 'o', 'u'}};
constexpr std::bitset<255> isVowel = []() {
  std::bitset<255> isVowel;
  for (char c : vowels) {
    isVowel.set(c);
  }
  return isVowel;
}();

class Solution {
 public:
  std::string sortVowels(std::string_view s) {
    // permute s to get a new string t such that:
    // - All consonants remain in their original places.
    // - Vowels must be sorted in in non-decreasing order of their ASCII.
    std::array<int, 255> frequency{};
    for (char c : s) {
      if (isVowel[c]) {
        ++frequency[c];
      }
    }

    int ptr = 0;
    auto getNextVowel = [&ptr, &frequency]() {
      while (frequency[vowels[ptr]] == 0) {
        ++ptr;
      }

      --frequency[vowels[ptr]];
      return vowels[ptr];
    };

    std::string result;
    result.reserve(s.size());
    for (char c : s) {
      if (isVowel[c]) {
        result += getNextVowel();
      } else {
        result += c;
      }
    }
    return result;
  }
};
