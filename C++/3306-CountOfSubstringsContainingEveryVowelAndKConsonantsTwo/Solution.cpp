#include <algorithm>
#include <array>
#include <string_view>

constexpr std::array<char, 5> vowels{{'a', 'e', 'i', 'o', 'u'}};

class Solution {
 public:
  long long countOfSubstrings(std::string_view word, int k) {
    auto countAtLeastK = [word](int k) -> long long {
      // Contain every vowel, and k consonants.
      // Sliding window of size at least 5 + k
      // Need to contract window, if consonants > k.
      std::array<int, 5> vowelFreq{};
      long long result = 0;
      int consonants = 0;
      int l = 0;
      for (int r = 0; r < word.size(); ++r) {
        auto it = std::find(vowels.begin(), vowels.end(), word[r]);
        if (it == vowels.end()) {
          // consonant
          ++consonants;
        } else {
          ++vowelFreq[it - vowels.begin()];
        }

        // shrink window while valid
        while (consonants >= k && std::find(vowelFreq.begin(), vowelFreq.end(),
                                            0) == vowelFreq.end()) {
          result += word.size() - r;
          auto it = std::find(vowels.begin(), vowels.end(), word[l]);
          if (it == vowels.end()) {
            // consonant
            --consonants;
          } else {
            --vowelFreq[it - vowels.begin()];
          }

          ++l;
        }
      }

      return result;
    };

    return countAtLeastK(k) - countAtLeastK(k + 1);
  }
};
