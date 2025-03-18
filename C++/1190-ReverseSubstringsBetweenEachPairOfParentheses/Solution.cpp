#include <stack>
#include <string>
#include <utility>
#include <vector>

class Solution {
 public:
  std::string reverseParentheses(std::string s) {
    int n = s.length();

    std::stack<int> openParenthesesIndices;
    std::vector<int> pairIndices(n);
    for (int i = 0; i < n; ++i) {
      if (s[i] == '(') {
        openParenthesesIndices.push(i);
      } else if (s[i] == ')') {
        int j = openParenthesesIndices.top();
        openParenthesesIndices.pop();

        pairIndices[i] = j;
        pairIndices[j] = i;
      } else {
        continue;
      }
    }

    std::string result;
    int direction = 1;
    for (int curr = 0; curr < n; curr += direction) {
      if (s[curr] == '(' || s[curr] == ')') {
        direction = -direction;  // change direction
        curr = pairIndices[curr];
      } else {
        result += s[curr];
      }
    }
    return result;
  }

  std::string reverseParenthesesWrong(std::string s) {
    std::vector<std::string> strs = std::vector<std::string>(s.length());
    for (std::string& str : strs) {
      str.reserve(s.length());
    }

    // Group substrings together
    int i = 0;
    for (char c : s) {
      if (c == '(') {
        ++i;
      } else if (c == ')') {
        --i;
      } else {
        strs[i] += c;
      }
    }

    // reverse the strings
    i = 0;
    for (std::string& str : strs) {
      if (i++ & 1) {
        reverse(str);
      }
    }

    i = 0;
    std::string result;
    result.reserve(s.length());
    for (char c : s) {
      if (c == '(') {
        ++i;
      } else if (c == ')') {
        --i;
      } else {
        char toAdd = strs[i][0];
        strs[i] = strs[i].substr(1, strs[i].length() - 1);
        result += toAdd;
      }
    }
    return result;
  }

 private:
  void reverse(std::string& s) {
    int n = s.size();
    for (int i = 0; i < n / 2; ++i) {
      std::swap(s[i], s[n - i - 1]);
    }
  }
};
