#include <algorithm>
#include <array>
#include <climits>
#include <cstdint>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

constexpr int ALPHABETS = 26;

class Solution {
  inline bool isConsistent(array<bool, ALPHABETS> const &expected,
                           string const &word) {
    bool consistent = true;
    for (char const &c : word) {
      // branchless!
      consistent = consistent * expected[c - 'a'];
    }
    return consistent;
  }

public:
  int countConsistentStrings(string allowed, vector<string> &words) {
    // allowed contains distinct characters.
    // A string is consistent if all its characters are also in allowed
    // only lower case characters
    array<bool, ALPHABETS> expected{};
    for (char const &c : allowed) {
      expected[c - 'a'] = true;
    }

    int count = 0;
    for (string const &word : words) {
      count += isConsistent(expected, word);
    }
    return count;
  }
};
