#include <array>
#include <string>
#include <string_view>
#include <vector>

class Solution {
 public:
  std::string robotWithString(std::string_view s) {
    // Given s, and empty string t.
    // Repeat until both are empty:
    // 1. Remove first character of s, append to t, OR
    // 2. Remove last character of t, append to result.
    // Return the lexicographically smallest string.
    //
    // Greedy.
    std::array<int, 256> freq{};
    for (char c : s) {
      ++freq[c];
    }

    std::string result;
    result.reserve(s.size());

    std::vector<char> t;
    t.reserve(s.size());

    char minChar = 'a';
    for (char c : s) {
      t.emplace_back(c);
      --freq[c];

      // determine the current minCharacter.
      while (minChar != 'z' && freq[minChar] == 0) {
        ++minChar;
      }

      // every character smaller than the current minChar in s is written
      // in reverse, i.e., popped off the stack.
      while (!t.empty() && t.back() <= minChar) {
        result += t.back();
        t.pop_back();
      }
    }
    return result;
  }
};
