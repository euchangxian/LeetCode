#include <iostream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;
class Solution {
 private:
  void reverse(string& s) {
    int n = s.size();
    for (int i = 0; i < n / 2; ++i) {
      swap(s[i], s[n - i - 1]);
    }
  }

 public:
  string reverseParentheses(string s) {
    int n = s.length();

    stack<int> openParenthesesIndices;
    vector<int> pairIndices(n);
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

    string result;
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

  string reverseParenthesesWrong(string s) {
    vector<string> strs = vector<string>(s.length());
    for (string& str : strs) {
      str.reserve(s.length());
    }

    // Group substrings together
    int i = 0;
    for (char const& c : s) {
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
    for (string& str : strs) {
      if (i++ & 1) {
        reverse(str);
      }
    }

    i = 0;
    string result;
    result.reserve(s.length());
    for (char const& c : s) {
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
};

int main() {
  cout << Solution().reverseParentheses("(abcd)") << endl;
  cout << Solution().reverseParentheses("(u(love)i)") << endl;
  cout << Solution().reverseParentheses("(ed(et(oc))el)") << endl;
  cout << Solution().reverseParentheses("a(bcdefghijkl(mno)p)q") << endl;
}
