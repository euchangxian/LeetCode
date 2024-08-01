#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;
class Solution {
public:
  vector<vector<string>> groupAnagrams(vector<string> &strs) {
    unordered_map<string, vector<string>> groups;

    for (string s : strs) {
      string sorted = s;
      sort(sorted.begin(), sorted.end());

      groups[sorted].push_back(s);
    }

    vector<vector<string>> result;
    for (auto const &[key, group] : groups) {
      result.push_back(group);
    }

    return result;
  }
};
