#include <array>
#include <string_view>
#include <utility>

constexpr int MOD = 1E9 + 7;
class Solution {
 public:
  int lengthAfterTransformations(std::string_view s, int t) {
    // string s, integer t representing the number of transformations to perform
    // In one transformation, every character in s is replaced:
    // - If the character is 'z', replace with "ab"
    // - Otherwise, replace with the next character in the alphabet
    // Return the length after t transformations.
    //
    // We do not necessarily have to simulate the replacement.
    // The length will only increase when the character is 'z'.
    // The next consideration is when after transformation, tracking the "ab".
    // But that can be derived too.
    //
    // Starting from "a", the number of transformations before the length
    // increases is:
    // - 26, +1
    // - 26, +2
    // - 26, +4
    // i.e., for whole cycles, we essentially double the length.
    // For a pattern "ab", the string after 25 transformations is "zab", then
    // 26: "abbc"
    // 24: "yzzab" -> 25: "zababbc" -> 26: "abbcbccd"
    // 23: "xyyzyzzab" -> 24: "yzzabzababbc" -> 25: "zababbcabbcbccd" -> ...
    // In between, we have:
    // - (26, +1)
    // - (25, +1), (26, +1)
    // - (24, +1), (25, +2), (26, +1)
    // - (23, +1), (24, +3), (25, +3), (26, +1)
    // which looks very much like Pascal's Triangle? (dp[i] = dp[i-1]+dp[i])
    // 1
    // 1 1
    // 1 2 1
    // 1 3 3 1
    // 1 4 6 4 1
    // 1 5 10 10 5 1
    //
    // Hm. wrong approach. Keep track of the number of characters after each
    // transformation.
    std::array<int, 26> curr{};
    for (char c : s) {
      ++curr[c - 'a'];
    }

    for (int i = 0; i < t; ++i) {
      std::array<int, 26> next{};
      next[0] = curr[25];                    // 'z' -> 'a'
      next[1] = (curr[25] + curr[0]) % MOD;  // 'z' -> 'b', 'a' -> 'b'
      for (int i = 2; i < 26; ++i) {
        next[i] = curr[i - 1];
      }
      curr = std::move(next);
    }

    int result = 0;
    for (int i = 0; i < 26; ++i) {
      result = (result + curr[i]) % MOD;
    }
    return result;
  }
};
