#include <cstddef>
#include <cstdlib>
#include <string>

class Solution {
 public:
  int minMovesToMakePalindrome(std::string s) {
    // In one move, select any two adjacent characters of s and swap them.
    // Return minimum number of moves to make s a palindrome.
    // Input is guaranteed to be palindrom-able.
    //
    // I HATE PALINDROMES.
    // How to even determine the optimal palindrome, given that there can be
    // multiple permutations?
    // Try expanding the prefix? similar to prefix=suffix[::-1]?
    //
    // WARNING: Tapped out. I HATE PALINDROMES.
    // Core Insight: Partition into prefix and suffix. e.g., "abb|acc".
    // Notice that 'b' and 'c' have characters in the same partition, which we
    // want to "fix".
    // However, moving the rightmost 'b' that is "closer" to the right will be
    // the unoptimal choice. e.g., "aba|cbc" -> "cab|abc" -> "cba|abc".
    // This is because in the initial string, we already have the palindromic
    // pairs (a, b), and (b, a). By swapping the right-most 'b' with the 'a'
    // in the suffix, we break that order, which will need to be restored later.
    // Thus, we want to fix the (a, c) and (b, c) ordering, by moving the
    // left-most 'c'.
    // "abb|acc" -> "abb|cac" -> "abc|bac" -> "acb|bac" -> "cab|bac".
    // By doing this, we introduce the palindromes "caac" and "cbbc", without
    // breaking our existing palindromic subsequences.
    // If there is a character that cannot be paired i.e., odd frequency,
    // then we want to move that character to the centre.
    //
    // NOTE: Note that there can only be at most one character that has an ODD
    // frequency, given that the input can always be made a valid palindrome.
    //
    // Okay. Now, how to implement???
    // "abb|acc", n = 6
    //  ^   ^     => n-1-3 = 2swaps
    // "bb|cc", n = 4
    //  ^^        => n-1-1 = 2 swaps
    // "cc",    n = 2
    // Though, we want to iterate from the back, since pop_front is expensive.
    // O(n^2). Can be improved with Fenwick Trees, similar to
    // 1505. Minimum Possible Integer after at most K Adjacent Swaps on Digit.
    int count = 0;
    while (!s.empty()) {
      int i = s.find(s.back());
      if (i != s.size() - 1) {
        // if the character found is NOT the same as the back.
        count += i;
        s.erase(i, 1);
      } else {
        count += i / 2;
      }
      s.pop_back();
    }
    return count;
  }
};
