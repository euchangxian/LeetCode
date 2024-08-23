#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
private:
  // Note that unlike usual backtracking solutions where the reference of
  // the current vector/string is passed in like &current, this one requires
  // pass-by-value.
  void dfs(string const &digits, vector<vector<char>> const &mappings,
           vector<string> &combinations, string current, int i) {
    if (i >= digits.length()) {
      combinations.push_back(current);
      return;
    }

    vector<char> letters = mappings[digits[i] - '0'];
    for (char letter : letters) {
      // No backtracking. Trying each character combination out.
      dfs(digits, mappings, combinations, current + letter, i + 1);
    }
  }

public:
  vector<string> letterCombinations(string digits) {
    if (digits.empty()) {
      return {};
    }
    vector<vector<char>> mappings = {{},
                                     {},
                                     {'a', 'b', 'c'},
                                     {'d', 'e', 'f'},
                                     {'g', 'h', 'i'},
                                     {'j', 'k', 'l'},
                                     {'m', 'n', 'o'},
                                     {'p', 'q', 'r', 's'},
                                     {'t', 'u', 'v'},
                                     {'w', 'x', 'y', 'z'}};

    vector<string> combinations;
    dfs(digits, mappings, combinations, "", 0);
    return combinations;
  }
};
