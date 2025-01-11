#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <string_view>

class Solution {
 public:
  bool canConstruct(std::string_view s, int k) {
    // Problem requires constructing k number of palindromes, using ALL the
    // characters in S, NOT counting k-length palindromes.
    // Intuition involves counting the frequency of each character, since
    // the characters can be re-ordered arbitrarily.
    // Otherwise, this seems like a construction/parity problem?
    // If k = 1, then check that at most 1 character has odd frequency.
    // If k = 2, then at most 2 can be odd, distributed among the two
    // palindromes.
    // ... and so on?
    // Can we prove it?
    // If there are > k odd frequency, then by pigeonhole principle, at least
    // one of the constructed strings must have at least two odd-occurence
    // characters, which makes it impossible to be a palindrome.
    if (s.size() <= k) {
      // either strings of length 1 => true, since trivially palindromes,
      // or false: no empty strings.
      return s.size() == k;
    }

    // use a bitmask instead.
    int frequency = 0;
    // std::array<int, 26> frequency{};
    for (char c : s) {
      // ++frequency[c-'a'];
      frequency ^= (1 << (c - 'a'));
    }

    // int numOdd =
    //     std::ranges::count_if(frequency.begin(), frequency.end(),
    //                           [](int freq) -> bool { return freq & 1; });
    int numOdd = __builtin_popcount(frequency);
    return numOdd <= k;
  }
};
