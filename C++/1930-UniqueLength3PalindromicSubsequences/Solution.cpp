#include <array>
#include <cstddef>
#include <cstdlib>
#include <string_view>
#include <utility>
#include <vector>

class Solution {
 public:
  int countPalindromicSubsequence(std::string_view s) {
    // Count unique palindromes of length 3 that are subsequences of s.
    // Length 3 => a _ a
    // i.e., As long as first and last characters are equal, then the
    // subsequence is a valid palindrome.
    // Though, we want unique ones.
    // Hmmmm...
    // For longest palindrome, recall LIS(s, reverse(s)).
    // What about frequency array? Each time freq[c] == 2, count number of
    // distinct characters, i.e., freq[x] >= 1 (must handle freq[c] >= 3)
    // Would this lead to double-counting?
    // IDTS. The method counts the number of 3-palindromes that start and ends
    // with character c.
    // Oh, under-counting, if we only count when freq[c] == 2.
    // Could be resolved using a 2D array though, with the inner array acting as
    // a `distinct`/`visited`. But runtime is bad? O(26n).
    // Overcounting too, when alphabets outside the prefix frequency is counted.
    // Can we do better?
    // Memorize the first and last index of each unique character?
    // Then obtain the frequency within (using prefix frequencies).
    // O(n) iterate and update frequencies.
    // Then, for 26 characters, obtain the frequency array between first and
    // last index. O(26^2), count distinct. Possibly slower but less space.
    constexpr std::size_t NUM_ALPHAS{26};

    // NOTE: we want exclusive [first, last], thus the size does not need to +1.
    std::vector<std::array<int, NUM_ALPHAS>> prefix(
        s.size(), std::array<int, NUM_ALPHAS>{});

    std::array<std::pair<int, int>, NUM_ALPHAS> indices;
    indices.fill(std::pair<int, int>{-1, -1});

    ++prefix[0][s[0] - 'a'];
    indices[s[0] - 'a'].first = 0;
    for (std::size_t i = 1; i < s.size(); ++i) {
      int idx = s[i] - 'a';
      prefix[i] = prefix[i - 1];
      ++prefix[i][idx];

      if (indices[idx].first == -1) {
        // Only take the first occurence.
        indices[idx].first = i;
      } else {
        // second or more occurence, take the lastest.
        indices[idx].second = i;
      }
    }

    int count = 0;
    for (int i = 0; i < NUM_ALPHAS; ++i) {
      auto [first, last] = indices[i];
      if (last == -1) {
        continue;
      }

      // obtain the frequency for this exclusive [first..last] range.
      // note that the size of the prefix array is equal to n.
      // Thus, prefix[first] includes s[first], prefix[last-1] excludes s[last].
      // Taking the complement, both s[first] and s[last] would be excluded.
      std::array<int, NUM_ALPHAS> freq{};
      for (int j = 0; j < NUM_ALPHAS; ++j) {
        freq[j] = prefix[last - 1][j] - prefix[first][j];
      }

      for (int j = 0; j < NUM_ALPHAS; ++j) {
        count += freq[j] >= 1;
      }
    }
    return count;
  }
};
