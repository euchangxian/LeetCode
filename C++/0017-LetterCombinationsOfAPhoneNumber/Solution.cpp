#include <string>
#include <vector>

class Solution {
 private:
  // Note that unlike usual backtracking solutions where the reference of
  // the current vector/string is passed in like &current, this one requires
  // pass-by-value.
  void dfs(std::string const& digits,
           std::vector<std::vector<char>> const& mappings,
           std::vector<std::string>& combinations,
           std::string current,
           int i) {
    if (i >= digits.length()) {
      combinations.push_back(current);
      return;
    }

    std::vector<char> letters = mappings[digits[i] - '0'];
    for (char letter : letters) {
      // No backtracking. Trying each character combination out.
      dfs(digits, mappings, combinations, current + letter, i + 1);
    }
  }

 public:
  std::vector<std::string> letterCombinations(std::string digits) {
    if (digits.empty()) {
      return {};
    }
    std::vector<std::vector<char>> mappings = {{},
                                               {},
                                               {'a', 'b', 'c'},
                                               {'d', 'e', 'f'},
                                               {'g', 'h', 'i'},
                                               {'j', 'k', 'l'},
                                               {'m', 'n', 'o'},
                                               {'p', 'q', 'r', 's'},
                                               {'t', 'u', 'v'},
                                               {'w', 'x', 'y', 'z'}};

    std::vector<std::string> combinations;
    dfs(digits, mappings, combinations, "", 0);
    return combinations;
  }
};
