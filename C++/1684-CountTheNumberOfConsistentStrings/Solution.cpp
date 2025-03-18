#include <array>
#include <string>
#include <vector>

constexpr int ALPHABETS = 26;

class Solution {
 public:
  int countConsistentStrings(std::string allowed,
                             std::vector<std::string>& words) {
    // allowed contains distinct characters.
    // A string is consistent if all its characters are also in allowed
    // only lower case characters
    std::array<bool, ALPHABETS> expected{};
    for (char c : allowed) {
      expected[c - 'a'] = true;
    }

    int count = 0;
    for (const std::string& word : words) {
      count += isConsistent(expected, word);
    }
    return count;
  }

 private:
  bool isConsistent(const std::array<bool, ALPHABETS>& expected,
                    const std::string& word) {
    bool consistent = true;
    for (char c : word) {
      // branchless!
      consistent = consistent * expected[c - 'a'];
    }
    return consistent;
  }
};
