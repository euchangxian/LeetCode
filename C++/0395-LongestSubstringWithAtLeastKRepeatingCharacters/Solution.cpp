#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <string_view>

class Solution {
 private:
  int countUnique(std::string_view s) {
    unsigned int seen = 0;  // bitmasks for seen characters, just for fun
    for (char c : s) {
      seen |= (1U << (c - 'a'));
    }
    return __builtin_popcount(seen);
  }

 public:
  int longestSubstring(std::string_view s, int k) {
    // Divide and Conquer solution is way more intuitive.
    if (s.size() == 0 || k > s.size()) {
      // s.size == 0 is self-explanatory. k > s.size is because even if s
      // contains all duplicate chars, the condition can never be met.
      return 0;
    }

    std::array<int, 26> count{};
    for (char c : s) {
      ++count[c - 'a'];
    }

    // we want to split where the count is < k. This is because that character
    // can never be included in any substring to be considered.
    for (int i = 0; i < s.size(); ++i) {
      if (count[s[i] - 'a'] < k) {
        int left = longestSubstring(s.substr(0, i), k);
        int right = longestSubstring(s.substr(i + 1), k);
        return std::max(left, right);
      }
    }

    // no split found, return entire substring, as it's valid.
    return s.size();
  }

  int longestSubstringSlidingWindow(std::string_view s, int k) {
    // Not too sure... First intuition was sliding window, but when can we be
    // sure that we dont need the element on the left, i.e., shrink the window?
    // Firstly, even if the left-most does not have sufficient count, it is not
    // possible to determine that another duplicate char may increase the count
    // sufficiently.
    // What about traversing the string once to count every character?
    // We can probably gain info about characters with insufficient count.
    // Those characters can never appear in our longest substring.
    // i.e., an O(n) traversal to collect the count of characters.
    // Then iterate through again, maintaining the substring length.
    // Suppose we encounter a character that has < k occurences, we restart
    // the substring length and begin counting again.
    // Not correct. This assumes that the count of characters in the substring
    // would be considered valid, since the count is valid in the whole string.

    int uniqueCharsCount = countUnique(s);

    // Try every substring with up to maxUnique number of unique characters.
    // The reason this works is because it provides us a way to expand/shrink
    // the window, testing substrings efficiently.
    // Using the uniqueCharsCount seems quite arbitrary, but somehow results in
    // the correct answer. Why so?
    // This is because each valid substring must have some number of unique
    // characters, say U.
    // Each of these U characters must appear >= k times.
    // By enumerating each U, we cover all possibilities, transforming the
    // problem into: "Find longest substring with exactly T unique characters,
    // where each of these characters appear >= k times", which is also a
    // sliding window question, where the number of distinct characters is our
    // condition to expand/shrink the window.
    int longest = 0;
    for (int maxUnique = 1; maxUnique <= uniqueCharsCount; ++maxUnique) {
      // our condition for expanding/shrinking the window.
      int unique = 0;

      // our problem constraint
      int atLeastKChars = 0;

      std::array<int, 26> count{};

      int l = 0;
      for (int r = 0; r < s.size(); ++r) {
        // Check if the current count is 0, if so, then we found a new character
        // increment count.
        unique += count[s[r] - 'a']++ == 0;

        // Check if the incremented count >= k
        // "==" is used because we only want to count this once, instead of
        // counting each time we increment
        atLeastKChars += count[s[r] - 'a'] == k;

        while (unique > maxUnique) {
          // Check if the current count is equal to k. if so, minusing it will
          // cause it to drop below k.
          atLeastKChars -= count[s[l] - 'a'] == k;

          // lol. i.e., reduce count, increment/shrink window, check if the
          // count has reached 0. If so, then we can reduce the number of unique
          // characters in our window.
          unique -= --count[s[l++] - 'a'] == 0;
        }

        // only update if conditions are met: atLeastKChars == unique, i.e.,
        // all characters in this substring occur at least k times.
        if (atLeastKChars == unique) {
          longest = std::max(longest, r - l + 1);
        }
      }
    }
    return longest;
  }
};
