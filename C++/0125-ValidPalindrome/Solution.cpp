#include <cctype>
#include <string>

using namespace std;

bool isalphanumeric(char c) { return isalpha(c) || isdigit(c); }

class Solution {
public:
  bool isPalindrome(string s) {
    int i = 0;
    int j = s.size() - 1;

    while (i < j) {
      while (!isalphanumeric(s[i]) && i < j) {
        ++i;
      }

      while (!isalphanumeric(s[j]) && i < j) {
        --j;
      }

      if (i >= j) {
        break;
      }

      char left = tolower(s[i++]);
      char right = tolower(s[j--]);
      if (left != right) {
        return false;
      }
    }
    return true;
  }
};
