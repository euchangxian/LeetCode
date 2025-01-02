#include <bitset>
#include <cstddef>
#include <cstdlib>
#include <string>
#include <vector>

constexpr std::bitset<26> isVowel = []() -> std::bitset<26> {
  std::bitset<26> vowel{};
  for (char v : {'a', 'e', 'i', 'o', 'u'}) {
    vowel.set(v - 'a');
  }
  return vowel;
}();

class Solution {
 public:
  std::vector<int> vowelStrings(std::vector<std::string>& words,
                                std::vector<std::vector<int>>& queries) {
    // query[i] = [l, r], to find the number of strings in words[l..r] inclusive
    // that start and end with a vowel {'a', 'e', 'i', 'o', 'u'}
    // Hm, just do a prefix preprocessing of the number of words that start with
    // a vowel.

    // Start and End with vowel
    auto pred = [](std::string_view word) -> int {
      return isVowel.test(word[0] - 'a') && isVowel.test(word.back() - 'a');
    };

    std::vector<int> prefix(words.size() + 1, 0);
    prefix[0] = pred(words[0]);

    for (int i = 1; i < words.size() + 1; ++i) {
      prefix[i] = prefix[i - 1] + pred(words[i - 1]);
    }

    std::vector<int> answer;
    answer.reserve(queries.size());
    for (const auto& query : queries) {
      int l = query[0];
      int r = query[1];  // inclusive end

      answer.push_back(prefix[r + 1] - prefix[l]);
    }
    return answer;
  }
};
