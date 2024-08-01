#include <cctype>
#include <string>
#include <vector>

using namespace std;
class Solution {
private:
  char DELIMITER = '#';

public:
  string encode(vector<string> &strs) {
    string result;
    for (string str : strs) {
      result += to_string(str.size()) + DELIMITER + str;
    }
    return result;
  }

  vector<string> decode(string s) {
    vector<string> result;
    int i = 0;
    while (i < s.size()) {
      int j = i;
      while (s[j] != DELIMITER) {
        ++j;
      }

      int numTokens = stoi(s.substr(i, j - i));
      string str = s.substr(j + 1, numTokens);
      result.push_back(str);
      i = j + 1 + numTokens;
    }
    return result;
  }
};
