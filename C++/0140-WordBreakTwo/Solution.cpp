#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {
 public:
  std::vector<std::string> wordBreak(std::string s,
                                     std::vector<std::string>& wordDict) {
    std::unordered_set<std::string> wordSet =
        std::unordered_set<std::string>(wordDict.begin(), wordDict.end());

    std::unordered_map<std::string, std::vector<std::string>> memo;
    return dfs(s, wordSet, memo);
  }

  std::vector<std::string> dfs(
      std::string s,
      const std::unordered_set<std::string>& wordSet,
      std::unordered_map<std::string, std::vector<std::string>>& memo) {
    if (memo.count(s) > 0) {
      return memo[s];
    }

    if (s.empty()) {
      return {""};
    }

    std::vector<std::string> result;
    for (int end = 1; end <= s.size(); ++end) {
      std::string word = s.substr(0, end);
      if (wordSet.count(word) > 0) {
        std::vector<std::string> sublist = dfs(s.substr(end), wordSet, memo);
        for (std::string st : sublist) {
          if (st.empty()) {
            result.push_back(word);
          } else {
            result.push_back(word + " " + st);
          }
        }
      }
    }
    memo[s] = result;
    return result;
  }
};
