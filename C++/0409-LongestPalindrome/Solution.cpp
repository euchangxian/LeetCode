#include <string>
#include <unordered_map>

using namespace std;
class Solution {
public:
  int longestPalindrome(string s) {
    unordered_map<char, int> freq;
    for (char c : s) {
      if (freq.count(c) == 0) {
        freq[c] = 0;
      }
      ++freq[c];
    }
    bool hasOdd = false;
    int result = 0;
    for (auto const &[_, val] : freq) {
      if (val % 2 == 1) {
        hasOdd = true;
        result += val - 1;
        continue;
      }
      result += val;
    }
    return result + hasOdd;
  }
};
