#include <array>
#include <cstddef>
#include <cstdlib>
#include <string_view>

class Solution {
 public:
  int numTilePossibilities(std::string_view tiles) {
    // Collect frequency array.
    // For each letter as start, backtrack, recursively.
    std::array<int, 26> frequency{};
    for (char c : tiles) {
      ++frequency[c - 'A'];
    }

    return dfs(frequency);
  }

 private:
  int dfs(std::array<int, 26>& frequency) {
    int count = 0;
    for (int i = 0; i < 26; ++i) {
      if (frequency[i] == 0) {
        continue;
      }

      --frequency[i];
      count += 1 + dfs(frequency);
      ++frequency[i];
    }
    return count;
  }
};
