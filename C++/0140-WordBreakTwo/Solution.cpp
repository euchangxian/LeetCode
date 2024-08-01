#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
public:
  vector<string> wordBreak(string s, vector<string> &wordDict) {
    unordered_set<string> wordSet =
        unordered_set<string>(wordDict.begin(), wordDict.end());

    unordered_map<string, vector<string>> memo;
    return dfs(s, wordSet, memo);
  }

  vector<string> dfs(string s, unordered_set<string> const &wordSet,
                     unordered_map<string, vector<string>> &memo) {
    if (memo.count(s) > 0) {
      return memo[s];
    }
    if (s.empty()) {
      return {""};
    }
    vector<string> result;
    for (int end = 1; end <= s.size(); ++end) {
      string word = s.substr(0, end);
      if (wordSet.count(word) > 0) {
        vector<string> sublist = dfs(s.substr(end), wordSet, memo);
        for (string st : sublist) {
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

int main() {
  string s = "pineapplepenapple";
  vector<string> wordDict = {"apple", "pen", "applepen", "pine", "pineapple"};

  vector<string> result = Solution().wordBreak(s, wordDict);
  for (auto s : result) {
    cout << s << " ";
  }
  cout << endl;
}
