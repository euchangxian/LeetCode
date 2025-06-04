#include <string>
#include <string_view>

class Solution {
 public:
  std::string answerString(std::string_view word, int numFriends) {
    // In each round,
    // - word is aplit into numFriends non-empty strings, such that no previous
    //   rounds had the exact same split.
    // - All the split words are placed into a box.
    // Find the lexicographically largest string from the box.
    //
    // Hmm?? There isnt a need to simulate "rounds". The lexicographically
    // largest depends on the longest string such that n-1 friends have a split
    // of size 1.
    // Then, fixed size sliding window of word-(numFriends-1).
    // The expensive operation is the string comparison. Will rolling hashes
    // help?
    // Given word.length <= 5*10^3, the largest possible window occurs when
    // numFriends = 2, resulting in k=5*10^3 - 1 = 4999
    // Not feasible, since 26^4999, bound to have collisions.
    // Ahh... Not necessarily fixed-size sliding window...
    // Consider "aazz", numFriends=2
    // The answer is a string of size 2 < 3 "zz", not "azz".
    if (numFriends == 1) {
      return std::string{word};
    }
    const int n = word.size();
    const int k = n - (numFriends - 1);

    std::string_view result;
    for (int i = 0; i < n; ++i) {
      auto curr = word.substr(i, k);
      result = std::max(result, curr);
    }
    return std::string{result};
  }
};
