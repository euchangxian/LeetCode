#include <array>
#include <string>
#include <string_view>
#include <vector>

constexpr int BUCKETS = 26 * 26 + 26;
class Solution {
 public:
  int longestPalindrome(std::vector<std::string>& words) {
    // words[i].length = 2
    // Create the longest possible palindrome by selecting some elements in
    // words and concatenate them in any order. Each element can be chosen
    // at most once.
    // Return the length.
    //
    // Hm. Count frequency? Since words[i].length = 2, all palindromes created
    // must be even length. Thus, the frequency of characters in the resultant
    // palindrome must all be even.
    // Nah. What about looking for "opposites"? i.e., if we have "ab", then
    // if "ba" exists, we can use both.
    // Seems to be on the right-track.
    // The simplest is therefore an unordered_set, with a two-sum like
    // iteration.
    // Can we speed up the constant factors? 26*26=676. Thus, we can hash
    // each combination into a table of size 676.
    // Use a frequency table.
    //
    // Ah. Missing the case where c1 == c2. Then, it can be added trivially.
    // But this can only be done once, in the centre.
    // We also want to avoid the case like words = "aa", "cc", "aa",
    // Then, we would make "aa" the centre, forming "aa", instead of "aaccaa"
    std::array<int, BUCKETS> freq{};
    constexpr auto bucket = [&](char c1, char c2) -> int {
      return (c1 - 'a') * 26 + (c2 - 'a');
    };

    int palindromes = 0;
    int result = 0;
    for (std::string_view s : words) {
      bool isPalindrome = s[0] == s[1];

      int complement = bucket(s[1], s[0]);
      if (freq[complement]) {
        --freq[complement];
        result += 4;

        palindromes -= isPalindrome;
        continue;
      }

      palindromes += isPalindrome;
      ++freq[bucket(s[0], s[1])];
    }

    return result + (palindromes ? 2 : 0);
  }
};
